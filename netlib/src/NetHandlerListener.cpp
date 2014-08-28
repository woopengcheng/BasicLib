#include "NetHandlerListener.h"
#include "NetHelper.h"
#include "NetHandlerServer.h"
#include "ServerSession.h"
#include "INetReactor.h"
#ifdef WIN32
#include <WinSock.h>
#endif

namespace Net
{ 
	INT32 NetHandlerListener::Init( const char * pAddress , INT32 nPort , BOOL bResueAddr /*= TRUE */, INT32 nListenerCount /*= DEFAULT_LISTENER_COUNT*/ )
	{
		Bind(pAddress , nPort);
		return Listen(nListenerCount);
	}

	INT32 NetHandlerListener::Cleanup()
	{
		return FALSE;
	}

	NetHandlerListener::NetHandlerListener( INetReactor * pNetReactor , ISession * pSession)
		: INetHandler(pSession)
		, m_pNetReactor(pNetReactor)
	{
		SetSocket(::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP));

		int nValueTrue = 1;
		NetHelper::SetIOCtrl(GetSocket() , FIOASYNC , &nValueTrue);
	}

	INT32 NetHandlerListener::OnMsgRecving( void )
	{
		sockaddr_in addr = {0};
#ifdef __linux
		socklen_t nAddrLen = sizeof(sockaddr_in);
#else
		INT32 nAddrLen = sizeof(sockaddr_in);
#endif
		SOCKET socket = ::accept(GetSocket(),(sockaddr*)&addr , &nAddrLen);
		if( socket != -1)
		{
			NetHelper::SetSocket(socket);	 
			OnAccept(socket , &addr);
		}
		return NET_ERROR_SUCCESS;
	}

	INT32 NetHandlerListener::Listen( INT32 nListenerCount /*= DEFAULT_LISTENER_COUNT*/)
	{
		return ::listen(GetSocket() , nListenerCount);
	}

	INT32 NetHandlerListener::Bind( const char * pAddress , INT32 nPort , BOOL bResueAddr)
	{
		Assert_Re(pAddress , -1);
		 
		int nValueTrue = 1;
		if (bResueAddr)
		{
			setsockopt(GetSocket() , SOL_SOCKET , SO_REUSEADDR , (char *)&nValueTrue , sizeof(nValueTrue));
		}

		sockaddr_in addr = {0};
		addr.sin_family = AF_INET;
		addr.sin_port = htons(nPort);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		if (pAddress != 0 && strlen(pAddress) > 0)
		{
			addr.sin_addr.S_un.S_addr = ::inet_addr(pAddress);
		}

		return ::bind(GetSocket() , (sockaddr*)&addr , sizeof(sockaddr_in));
	}

	void NetHandlerListener::OnAccept( SOCKET socket , sockaddr_in * addr )
	{
		if (m_pNetReactor)
		{
			NetHandlerServer * pServer = new NetHandlerServer(new ServerSession);
			m_pNetReactor->AddNetHandler(pServer);
		}
	}


}