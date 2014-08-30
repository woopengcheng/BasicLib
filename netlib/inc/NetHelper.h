#ifndef __net_net_helper_h__
#define __net_net_helper_h__ 
#include "NetCommon.h" 

struct in_addr;

namespace Net 
{   
	class DLL_EXPORT NetHelper
	{
	public:  
		static void   SetSocket(SOCKET & socket);
		static INT32  SetIOCtrl(int s,long cmd,int *argp);
		static INT32  RecvMsg(SOCKET socket , char * pBuf , UINT32 unSize);
		static BOOL   IsSocketEagain();
		static INT32  NetToN( const char *ip, struct in_addr *addr );
	};
}

#endif
