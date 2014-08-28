#ifndef __msg_msg_proxy_h__
#define __msg_msg_proxy_h__ 
#include "MsgCommon.h"
#include "GenMsgHelper.h"
#include "ObjectMsgCall.h"

namespace Msg
{   

#define USE_MSG_PROXY
#ifdef USE_MSG_PROXY
	template<typename Object>
	static BOOL  local_call_Test(char p1 , INT16 p2, UINT16 p3 , INT32 p4 , UINT32 p5 , const char * p6 , Chunk p7 , std::vector<Object> vecTargets , Object objSrc , UINT16 usPriority = 0)
	{
		if (vecTargets.size() == 0)
		{
			return FALSE;
		}
		else
		{ 
			ObjectMsgCall<Object> * pMsg = new(sizeof(Object)*vecTargets.size())ObjectMsgCall<Object>;  

			GenMsgHelper::GenMsgCall<Object>(*pMsg , 0 , sz_local_call_Test , vecTargets , objSrc , usPriority);
			GenMsgHelper::GenMsgParams<Object>(*pMsg , p1 , p2 , p3 , p4 , p5 , p6 , p7);
			    
			InnerMsg<Object>::GetInstance().SendMsg(pMsg);
		}

		return TRUE;
	}
#endif 

#define DECLARE_MSG_WORLD_OBJECT public:\
	void  local_run_Object_Test(char p1 , INT16 p2, UINT16 p3 , INT32 p4 , UINT32 p5 , const char * p6 , Msg::Chunk p7 , std::vector<MSG_ID> vecTargets , MSG_ID objSrc);\

	template<typename Object>
	static BOOL  local_call_WorldTest(char p1 , INT16 p2, UINT16 p3 , INT32 p4 , UINT32 p5 , const char * p6 , Chunk p7 , std::vector<Object> vecTargets , Object objSrc , UINT16 usPriority = 0)
	{
		if (vecTargets.size() == 0)
		{
			return FALSE;
		}
		else
		{ 
			ObjectMsgCall<Object> * pMsg = new(sizeof(Object)*vecTargets.size())ObjectMsgCall<Object>;  

			GenMsgHelper::GenMsgCall<Object>(*pMsg , 0 , sz_local_call_WorldTest , vecTargets , objSrc , usPriority);
			GenMsgHelper::GenMsgParams<Object>(*pMsg , p1 , p2 , p3 , p4 , p5 , p6 , p7);

			InnerMsg<Object>::GetInstance().SendMsg(pMsg);
		}

		return TRUE;
	}

	template<typename Object>
	static void  local_run_Test(char p1 , INT16 p2, UINT16 p3 , INT32 p4 , UINT32 p5 , const char * p6 , Msg::Chunk p7 , std::vector<Object> vecTargets , Object objSrc)
	{
		printf("Local_run_test."); 
	} 

}
#endif