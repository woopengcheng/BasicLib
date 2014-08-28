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
		// Qualifier: ����New.���ֻ�Ǽ򵥵ĵ��õײ��New.ֻ�Ǵ�С��ȷ��.���������������һ��.ÿ��ֻ������������Ĵ�С�Ͳ����Ĵ�С�Լ�����Ĵ�С.
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
			return m_usPriority > obj.m_usPriority;  //5 ��С����,m_usPriorityС�����ȼ���
		}

	public: 
		virtual UINT32 Copy(ObjectMsgCall<Object> * pMsg);
		virtual UINT32 RefreshSize();

	public:      
		UINT32             m_unMsgID;                                  //5 ��Ϣ��ID,�ڽ����ڲ�.�������������������.
		UINT32             m_unMsgLength;                              //5 ������Ϣ�ĳ���
		char               m_szMsgMethod[MAX_MSG_METHOD_NAME_LENGTH];  //5 ������Ϣ�ĺ���
		Parameters         m_objParams;                                //5 ��Ϣ�����Ĳ���. 
		UINT16             m_usPriority;

		Object			   m_objSource;       //5 ��ϢԴ
		UINT32			   m_unTargetsCount;
		Object			   m_aTargets[];      //5 Ŀ�����������������,��������ʡ�ռ�.������һ������.�����Ĳ��ܱ�֤�������Ĵ�С.�������Ϸ�ͻ��˿��ܻ����Bug.�������ڲ�ͨ��.�������б�֤��.
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