#ifndef __net_net_handler_server_h__
#define __net_net_handler_server_h__ 
#include "NetHandlerTransit.h"

namespace Net 
{  
	class NetHandlerServer :public NetHandlerTransit
	{
	public:
		NetHandlerServer(ISession * pSession)
			: NetHandlerTransit(pSession) 
		{}
		virtual ~NetHandlerServer(){} 

	public:
		virtual INT32  OnClose( void )     ;

	public:
		virtual INT32 HandleMsg(UINT32 unMsgID, const char* pBuffer, UINT32 unLength);

	}; 

	DECLARE_BOOST_POINTERS(NetHandlerServer);
}

#endif 