#ifndef __msg_msg_queue_h__
#define __msg_msg_queue_h__
#include "MsgCommon.h"
#include "ObjectMsgCall.h"
#include "TimerInterface.h"
#include "MsgTimerNode.h"

namespace Msg
{ 
	template<typename Object>
	class MsgQueue : public Timer::TimerInterface
	{
	public:
		typedef tbb_priority_queue<ObjectMsgCall<Object>*> QueueMsgsT; 

	public:
		MsgQueue(){}
		virtual ~MsgQueue(){}

	public:
		virtual INT32    Init(void);
		virtual INT32    Cleanup(void);
		virtual INT32    SetTimer(ObjectMsgCall<Object> * pMsg , UINT32 unTimeInterval , UINT32 unStartTime = 0, UINT32 unTimes = 0, void * pObj = NULL , TimerCallBackFunc pFunc = NULL);

	public:
		virtual  INT32                    AddMsg(ObjectMsgCall<Object> * pMsg);
		virtual  INT32                    AddMsg(ObjectMsgCall<Object> * pMsg , UINT32  unTimeout);
		virtual  ObjectMsgCall<Object>  * FetchMsg();

	public:
		virtual INT32    Update(void); 
		

	public:
		QueueMsgsT m_queueMsgs; 
	}; 
	
	template<typename Object>
	INT32 MsgQueue<Object>::SetTimer( ObjectMsgCall<Object> * pMsg , UINT32 unTimeInterval , UINT32 unStartTime /*= 0*/, UINT32 unTimes /*= 0*/, void * pObj /*= NULL */, TimerCallBackFunc pFunc /*= NULL*/ )
	{
		if (m_pTimerStrategy)
		{
			MsgTimerNode<Object> * pNode = new MsgTimerNode<Object>(pMsg , TimerIDAutoAddOne() , unTimeInterval , unStartTime , unTimes , pObj , pFunc);
			m_pTimerStrategy->InsertNode( GetTimerIDCount() , pNode);

			return GetTimerIDCount(); 
		}

		return -1;
	}

	template<typename Object>
	INT32 MsgQueue<Object>::Init( void )
	{ 
		return TimerInterface::Init();
	}

	template<typename Object>
	INT32 MsgQueue<Object>::Cleanup( void )
	{
		return TimerInterface::Cleanup();
	}

	template<typename Object>
	INT32 MsgQueue<Object>::Update( void )
	{  
		Timer::Node<INT64> * pNodeInt64 = GetNode(0);
		if (!pNodeInt64)
		{
			return FALSE;
		}
		MsgTimerNode<Object> * pNode = pNodeInt64->GetClass<MsgTimerNode<Object> >();    //5 获取堆顶的元素.然后进行比较.

		if (pNode && pNode->GetTimeCount().IsExpired())
		{
			InternalMsgTask<Object> * pTask = new InternalMsgTask<Object>(pNode->GetMsgCall()); 
			ThreadPool::ThreadPoolInterface::GetInstance().AddTask(pTask);
			RemoveTimer(pNode->GetTimerID());
		}

		return TRUE;
	}

	template<typename Object>
	INT32 MsgQueue<Object>::AddMsg(ObjectMsgCall<Object> * pMsg )
	{
		Assert_Re0(pMsg);

		m_queueMsgs.push(pMsg);

		return TRUE; 
	} 

	template<typename Object>
	INT32 MsgQueue<Object>::AddMsg( ObjectMsgCall<Object> * pMsg , UINT32 unTimeout )
	{
		Assert_Re0(pMsg);
		return SetTimer(pMsg , unTimeout);
	}

	template<typename Object>
	ObjectMsgCall<Object> * MsgQueue<Object>::FetchMsg()
	{ 
		ObjectMsgCall<Object> * pMsg = NULL;
		if(!m_queueMsgs.try_pop(pMsg))
		{
			return NULL;
		}
		return pMsg;
	}

}
#endif