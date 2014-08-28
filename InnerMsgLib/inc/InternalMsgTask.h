#ifndef __msg_internal_msg_task_h__
#define __msg_internal_msg_task_h__ 
#include "MsgCommon.h"
#include "ThreadTask.h"
#include "ObjectMsgCall.h"

namespace Msg
{ 
	template<typename Object>
	class InternalMsgTask : public ThreadPool::ThreadTask
	{   
	public:
		InternalMsgTask(ObjectMsgCall<Object> * pMsg);
		virtual ~InternalMsgTask();

	public:
		virtual INT32 Update( void );

	public: 
		ObjectMsgCall<Object> * m_pMsg;

	};

	template<typename Object>
	InternalMsgTask<Object>::InternalMsgTask( ObjectMsgCall<Object> * pMsg )
		: ThreadPool::ThreadTask(DEFAULT_MSG_HANDLE_THREAD_ID , "InternalMsgTask") 
		, m_pMsg(pMsg)
	{  
	}

	template<typename Object>
	InternalMsgTask<Object>::~InternalMsgTask()
	{
	}

	template<typename Object>
	INT32 InternalMsgTask<Object>::Update( void )
	{
		if (m_pMsg)
		{ 
			MethodImpl<Object> * pMethodImpl = InnerMsg<Object>::GetInstance().GetMethodImpl(m_pMsg->m_szMsgMethod);
			Assert_Re0(pMethodImpl);

			ParaseMsgCall<Object> objParaseMsgCall;
			objParaseMsgCall.m_pMehtodImpl = pMethodImpl;
			objParaseMsgCall.m_pMsgCall = m_pMsg; 

			if (m_pMsg->m_unTargetsCount == 0)
			{
				pMethodImpl->m_pMethodImpl(&objParaseMsgCall);
			}
			else
			{
				for (UINT32 i = 0;i < m_pMsg->m_unTargetsCount;++i)
				{
					ICallableObject<Object> * pICallableObject = InnerMsg<Object>::GetInstance().GetCallableObject(m_pMsg->m_aTargets[i]);
					if (pICallableObject)
					{
						objParaseMsgCall.m_pObj = pICallableObject;
						pMethodImpl->m_pMethodImpl(&objParaseMsgCall);
					} 
				}  
			}
			SAFE_DELETE(m_pMsg);    //5 这里释放的是每个函数调用的时候那个指针.
			return TRUE;
		}

		return FALSE;
	}

}
#endif