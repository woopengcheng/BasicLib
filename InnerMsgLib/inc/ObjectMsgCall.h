#ifndef __msg_object_msg_call_h__
#define __msg_object_msg_call_h__
#include "ThreadLock.h"
#include "MsgCommon.h"
#include "Parameters.h"

#ifdef WIN32
#pragma warning(disable : 4200)
#endif

namespace Msg
{
	template<typename Object>
	class ObjectMsgCall
	{ 
	public:
		ObjectMsgCall() :m_unMsgID(0) ,m_unMsgLength(0) , m_unTargetsCount(0) , m_usPriority(0){}
		~ObjectMsgCall(){}

	public:
		//************************************
		// Method:    GetSize
		// FullName:  Msg::ObjectMsgCall<Object>::GetSize
		// Access:    virtual public 
		// Returns:   UINT32
		// Qualifier: 重载New.这个只是简单的调用底层的New.只是大小不确定.所以在这里更改了一下.每次只传入柔性数组的大小和参数的大小以及本体的大小.
		//************************************
		static void * operator new(size_t size , size_t unExtra)
		{
			return malloc(size + unExtra); 
		}

		void operator delete(void * p , size_t unExtra)
		{
			free(p); 
		}

		bool operator < (const ObjectMsgCall<Object> & obj)
		{
			return m_usPriority > obj.m_usPriority;  //5 从小到达,m_usPriority小的优先级高
		}

	public: 
		virtual UINT32 Copy(ObjectMsgCall<Object> * pMsg);
		virtual UINT32 RefreshSize();

	public:      
		UINT32             m_unMsgID;                                  //5 消息的ID,在进程内部.这个变量基本上无用了.
		UINT32             m_unMsgLength;                              //5 整个消息的长度
		char               m_szMsgMethod[MAX_MSG_METHOD_NAME_LENGTH];  //5 调用消息的函数
		Parameters         m_objParams;                                //5 消息函数的参数. 
		UINT16             m_usPriority;

		Object			   m_objSource;       //5 消息源
		UINT32			   m_unTargetsCount;
		Object			   m_aTargets[];      //5 目标采用柔性数组来做,这样更节省空间.但是有一个问题.真正的不能保证这个数组的大小.如果是游戏客户端可能会产生Bug.这里是内部通信.数据是有保证的.
	};

	template<typename Object>
	UINT32 ObjectMsgCall<Object>::RefreshSize()
	{
		m_unMsgLength = sizeof(ObjectMsgCall<Object>) + m_unTargetsCount*sizeof(Object) + m_objParams.GetSize(); 
		return m_unMsgLength;
	}

	template<typename Object>
	UINT32 ObjectMsgCall<Object>::Copy(ObjectMsgCall<Object> * pMsg)
	{  
		pMsg = new(sizeof(Object)*m_unTargetsCount)ObjectMsgCall<Object>;

		pMsg->m_unMsgID        = m_unMsgID;
		pMsg->m_unMsgLength    = m_unMsgLength; 
		pMsg->m_objSource      = m_objSource;
		pMsg->m_usPriority     = m_usPriority;
		pMsg->m_unTargetsCount = m_unTargetsCount;
		memcpy(pMsg->m_szMsgMethod , m_szMsgMethod , MAX_MSG_METHOD_NAME_LENGTH); 

		for (UINT32 i = 0;i < m_unTargetsCount;++i)
		{
			pMsg->m_aTargets[i] = m_aTargets[i];
		} 
 
		pMsg->m_objParams.Copy(&m_objParams); 
		return TRUE;
	} 
}
#endif