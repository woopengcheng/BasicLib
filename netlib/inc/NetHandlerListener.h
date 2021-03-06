#ifndef __net_net_handler_listener_h__
#define __net_net_handler_listener_h__  
#include "INetHandler.h"

struct sockaddr_in;

namespace Net 
{  
	class INetReactor;

	class DLL_EXPORT NetHandlerListener : public INetHandler
	{
	public:
		NetHandlerListener(  INetReactor * pNetReactor , ISession * pSession);
		virtual ~NetHandlerListener( void ){}  

	public:
		virtual INT32  OnMsgRecving( void );

	public:
		virtual INT32  Init(const char * pAddress , INT32 nPort , BOOL bResueAddr = TRUE , INT32  nListenerCount = DEFAULT_LISTENER_COUNT);
		virtual INT32  Cleanup();
		virtual void   OnAccept(SOCKET socket , sockaddr_in * addr);

	protected:
		INT32   Listen(INT32  nListenerCount = DEFAULT_LISTENER_COUNT);
		INT32   Bind(const char * pAddress , INT32 nPort , BOOL bResueAddr = TRUE);
	
	protected:
		INetReactor * m_pNetReactor;
	}; 

	DECLARE_BOOST_POINTERS(NetHandlerListener);

}

#endif
