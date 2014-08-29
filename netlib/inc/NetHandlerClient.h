#ifndef __net_net_handler_client_h__
#define __net_net_handler_client_h__ 
#include "NetHandlerTransit.h"

namespace Net 
{  
	class NetHandlerClient :public NetHandlerTransit
	{
	public:
		NetHandlerClient(ISession * pSession)
			: NetHandlerTransit(pSession)  
		{ 
			SOCKET socket = ::socket(AF_INET , SOCK_STREAM , 0);
			SetSocket(socket);
		}
		virtual ~NetHandlerClient(){} 

	public:
		virtual INT32  Init( const char* ip,int port );
		virtual INT32  Cleanup();

	public:
		virtual INT32 HandleMsg(UINT32 unMsgID, const char* pBuffer, UINT32 unLength);
		 
	private:
		INT32  Connect( const char* ip,int port );
	}; 

}

#endif


