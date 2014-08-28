#include "MsgProxy.h"

namespace Msg
{  
	template<typename Object>
	static void  local_call_Object_Test(char p1 , INT16 p2, UINT16 p3 , INT32 p4 , UINT32 p5 , const char * p6 , Chunk p7 , std::vector<Object> vecTargets , Object objSrc , UINT16 usPriority = 0)
	{ 
		if (vecTargets.size() == 0)
		{
			return FALSE;
		}
		else
		{ 
			ObjectMsgCall<Object> * pMsg = new(sizeof(Object)*vecTargets.size())ObjectMsgCall<Object>;  

			GenMsgHelper::GenMsgCall<Object>(*pMsg , 0 , sz_local_call_WorldTest , vecTargets , objSrc);
			GenMsgHelper::GenMsgParams<Object>(*pMsg , p1 , p2 , p3 , p4 , p5 , p6 , p7);

			InnerMsg<Object>::GetInstance().SendMsg(pMsg);
		}
	}
}