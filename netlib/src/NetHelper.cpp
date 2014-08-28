#include "NetHelper.h"
#ifdef WIN32
#include <Windows.h>  
#endif 

namespace Net
{ 

	void NetHelper::SetSocket( SOCKET & socket )
	{
		linger s = {0};
		s.l_onoff = 1;
		setsockopt(socket,SOL_SOCKET,SO_LINGER,(char*)&s,sizeof(linger));

		int valuetrue = 1;
		setsockopt(socket,SOL_SOCKET,SO_KEEPALIVE,(char*)&valuetrue,sizeof(int));

		SetIOCtrl(socket,FIOASYNC,&valuetrue);
	}

	UINT32 NetHelper::RecvMsg(SOCKET socket , char * pBuf , UINT32 unSize )
	{
#ifdef __linux
		return ::recv(socket , pBuf , unSize , MSG_DONTWAIT);
#else
		return ::recv(socket , pBuf , unSize , 0);
#endif
	}

	BOOL NetHelper::IsSocketEagain()
	{ 
#ifdef __linux
		int e = errno;
		return (e == EAGAIN || e == EINTR);
#else
		int e = WSAGetLastError();
		return e == WSAEWOULDBLOCK;
#endif 

	}

	INT32 NetHelper::SetIOCtrl( int s,long cmd,int *argp )
	{
#ifdef __linux
		return ::ioctl(s,cmd,argp);
#else
		return ioctlsocket(s,cmd,(u_long*)argp);
#endif

	}

	INT32 NetHelper::NetToN( const char *ip, struct in_addr *addr )
	{
#ifdef __linux
		return ::inet_aton(ip,addr);
#else
		addr->S_un.S_addr = ::inet_addr(ip);
		return 0;
#endif
	}
}