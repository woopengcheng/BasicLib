#ifndef __msg_msg_timer_node_h__
#define __msg_msg_timer_node_h__ 
#include "Node.h"
#include "TimeCount.h" 
#include "TimerNode.h"
#include "ObjectMsgCall.h"

namespace Msg
{   
	template<typename Object>
	class MsgTimerNode : public Timer::TimerNode
	{ 
	public:
		CLASS_TYPE_ID(MsgTimerNode<Object> , TimerNode , CTID_MsgTimerNode)

	public: 
		MsgTimerNode(ObjectMsgCall<Object> * pMsg , UINT32 unTimerID , UINT32 unTimeInterval , UINT32 unStartTime = 0, UINT32 unTimes = 0, void * pObj = NULL , TimerCallBackFunc pFunc = NULL)
			: Timer::TimerNode(unTimerID , unTimeInterval , unStartTime , unTimes , pObj , pFunc)
			, m_pMsg(pMsg)
		{
		}
		virtual   ~MsgTimerNode(){}

	public: 
		ObjectMsgCall<Object> * GetMsgCall(){ return m_pMsg; }

	private:
		ObjectMsgCall<Object> * m_pMsg ;
	};


}

#endif