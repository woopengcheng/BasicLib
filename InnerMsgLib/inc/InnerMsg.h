#ifndef __msg_inner_msg_h__
#define __msg_inner_msg_h__
#include "ThreadTask.h"
#include "InternalMsgTask.h"
#include "ObjectMsgCall.h"
#include "MsgQueue.h" 
#include "ThreadPoolInterface.h"
#include "TimerHelp.h"
#include "MsgDispatcher.h"

namespace Msg
{ 
	template<typename Object>
	class InnerMsg : public ThreadPool::ThreadSustainTask , public MsgDispatcher<Object>
	{
	public:
		InnerMsg(): ThreadPool::ThreadSustainTask(DEFAULT_MSG_THREAD_ID , "ThreadSustainTask" , FALSE){}
		virtual ~InnerMsg(){}

	public:
		static InnerMsg & GetInstance()
		{
			static InnerMsg m_sInnerMsg;
			return m_sInnerMsg;
		}

	public:
		virtual  INT32  Init( UINT32 unMsgThreadPriorityCount = 1 , UINT32 unMsgHandlerthreadPriorityCount = 1, UINT32 unMsgThreadPriority = DEFAULT_MSG_THREAD_ID ,UINT32 unMsgHandlerthreadPriority = DEFAULT_MSG_HANDLE_THREAD_ID );
		virtual  INT32  Cleanup( void );
		virtual  INT32  Update( void ); 

	public:
		INT32  SendMsg(ObjectMsgCall<Object> * pMsg); 

	private:
		MsgQueue<Object>  m_objMsgQueue;
	}; 
	 
	template<typename Object>
	INT32 InnerMsg<Object>::Init(UINT32 unMsgThreadPriorityCount /*= 1*/ , UINT32 unMsgHandlerthreadPriorityCount /*= 1*/, UINT32 unMsgThreadPriority /*= DEFAULT_MSG_THREAD_ID*/ ,UINT32 unMsgHandlerthreadPriority /*= DEFAULT_MSG_HANDLE_THREAD_ID*/)
	{ 
		ThreadPool::ThreadPoolInterface::GetInstance().Init(std::map<UINT32 , UINT32>() , TRUE);
		ThreadPool::ThreadPoolInterface::GetInstance().Startup();
		ThreadPool::ThreadPoolInterface::GetInstance().CreateThread(unMsgThreadPriority , unMsgThreadPriorityCount);  //5 创建一个全局的计时器线程.
		ThreadPool::ThreadPoolInterface::GetInstance().CreateThread(unMsgHandlerthreadPriority , unMsgHandlerthreadPriorityCount);  //5 创建处理计时器任务的线程.

		ThreadPool::ThreadPoolInterface::GetInstance().AddTask(this);

		return TRUE;
	}

	template<typename Object>
	INT32 InnerMsg<Object>::Cleanup( void )
	{
 		ThreadPool::ThreadPoolInterface::GetInstance().Cleanup();

		return FALSE;
	}

	template<typename Object>
	INT32 InnerMsg<Object>::SendMsg( ObjectMsgCall<Object> * pMsg )
	{ 
		return m_objMsgQueue.AddMsg(pMsg);
	} 

	template<typename Object>
	INT32 InnerMsg<Object>::Update( void )
	{   
		ObjectMsgCall<Object> * pMsg = m_objMsgQueue.FetchMsg();
		if (pMsg)
		{ 
			return ThreadPool::ThreadPoolInterface::GetInstance().AddTask(new InternalMsgTask<Object>(pMsg)); 
		} 
		else
		{
			Timer::TimerHelper::sleep(1);
		} 
		return FALSE;
	}
}
#endif