#include "NetReactorEpoll.h"

namespace Net
{ 
	INT32 NetReactorEpoll::Init( void )
	{

		return NET_ERROR_FAILURE;
	}

	INT32 NetReactorEpoll::Cleanup( void )
	{

		return NET_ERROR_FAILURE;
	}

	INT32 NetReactorEpoll::Update( void )
	{

		return NET_ERROR_FAILURE;
	}

	INT32 NetReactorEpoll::AddNetHandler( INetHandler * pNetHandler , ENetHandlerFuncMask objMask /*= NET_FUNC_DEFAULT*/ )
	{

		return NET_ERROR_FAILURE;
	}

	INT32 NetReactorEpoll::DelNetHandler( INetHandler * pNetHandler )
	{

		return NET_ERROR_FAILURE;
	}

	INT32 NetReactorEpoll::ModNetHandler( INetHandler * pNetHandler , ENetHandlerFuncMask objMask )
	{

		return NET_ERROR_FAILURE;
	}

}