#ifndef __net_i_net_reactor_h__
#define __net_i_net_reactor_h__ 
#include "INetHandler.h"
#include "NetCommon.h"

#ifdef WIN32
#include <Windows.h>
#endif

namespace Net 
{  
	enum ENetHandlerFuncMask
	{
		NET_FUNC_READ    = 0x0001 ,
		NET_FUNC_WRITE   = 0x0002 ,
		NET_FUNC_ACCEPT  = 0x0004 ,
		NET_FUNC_EXCEPT  = 0x0008 ,
		NET_FUNC_EPOLLET = 0x0010 ,   //5 默认使用ET模式,只通知一次,然后不断的去接收数据.
		NET_FUNC_EPOLLLT = 0x0020 ,   //5 使用LT模式,只要有数据就不停的通知,然后一直接收
		NET_FUNC_TIMEOUT = 0x0040 ,

		NET_FUNC_DEFAULT = NET_FUNC_READ | NET_FUNC_WRITE | NET_FUNC_ACCEPT | NET_FUNC_EXCEPT | NET_FUNC_TIMEOUT,
		NET_FUNC_DEFAULT_AND_TIMEOUT = NET_FUNC_READ | NET_FUNC_WRITE | NET_FUNC_ACCEPT | NET_FUNC_EXCEPT ,
	};

	class INetReactor
	{
	public:
		INetReactor( void )
		{
		}
		virtual ~INetReactor( void )
{
}

	public:
		virtual INT32   Init( void ) = 0;
		virtual INT32   Cleanup( void ) = 0;
		virtual INT32   Update( void ) = 0;

	public:
		virtual INT32   AddNetHandler(INetHandler * pNetHandler , ENetHandlerFuncMask objMask = NET_FUNC_DEFAULT) = 0;
		virtual INT32   DelNetHandler(INetHandler * pNetHandler) = 0;
		virtual INT32   ModNetHandler(INetHandler * pNetHandler , ENetHandlerFuncMask objMask) = 0;
	}; 
	 
}

#endif
