#include "NetReactorSelect.h"

#ifdef WIN32
#include <windows.h>
#endif

namespace Net
{ 
	NetReactorSelect::NetReactorSelect( UINT32 unMaxConnectionCount )
		: m_nNetHandlerCount(0)
		, m_unMaxConnectionCount(unMaxConnectionCount) 
		, m_pFdSetReads(NULL)
		, m_pFdSetWrites(NULL)
		, m_pFdSetExcepts(NULL)
	{  

		size_t  size = /*unMaxConnectionCount * sizeof(void*) +*/ sizeof(fd_set);
		m_pFdSetReads = malloc(size);
		m_pFdSetWrites = malloc(size);
		m_pFdSetExcepts = malloc(size);

		memset(m_pFdSetReads , 0 , size);
		memset(m_pFdSetWrites , 0 , size);
		memset(m_pFdSetExcepts , 0 , size);
	}

	NetReactorSelect::~NetReactorSelect( void )
	{  
		free(m_pFdSetReads);
		free(m_pFdSetWrites);
		free(m_pFdSetExcepts);

	}

	INT32 NetReactorSelect::Init( void )
	{

		return NET_ERROR_SUCCESS;
	}

	INT32 NetReactorSelect::Cleanup( void )
	{ 
		MapNetHandlersT::iterator iter = m_mapNetHandlers.begin();
		for (;iter != m_mapNetHandlers.end();++iter)
		{
			SAFE_DELETE(iter->second); 
		}
		m_mapNetHandlers.clear();
		m_mapNetEvents.clear();

		return NET_ERROR_SUCCESS;
	}

	INT32 NetReactorSelect::Update( void )
	{
		if (m_nNetHandlerCount == 0)
		{
			return NET_ERROR_FAILURE;
		}

		fd_set* pFdSetWrites = (fd_set*)m_pFdSetWrites;
		fd_set* pFdSetReads =  (fd_set*)m_pFdSetReads;
		fd_set* pFdSetExcepts = (fd_set*)m_pFdSetExcepts;

		FD_ZERO(pFdSetExcepts);
		FD_ZERO(pFdSetReads);
		FD_ZERO(pFdSetWrites); 

		{ 
			MapNetEventsT::iterator iterEvents = m_mapNetEvents.begin();
			MapNetHandlersT::iterator iterHandlers = m_mapNetHandlers.begin();
			for (;iterEvents != m_mapNetEvents.end() && iterHandlers != m_mapNetHandlers.end() ;++iterEvents , ++ iterHandlers)
			{
				SOCKET socket = iterHandlers->second->GetSocket();
				if (iterEvents->second & (NET_FUNC_READ | NET_FUNC_ACCEPT)) 
					FD_SET(socket , pFdSetReads); 
				if (iterEvents->second & NET_FUNC_WRITE) 
					FD_SET(socket , pFdSetWrites); 
				if (iterEvents->second & NET_FUNC_EXCEPT) 
					FD_SET(socket , pFdSetExcepts);   
			}
		}

		struct timeval objTimeout = {0};
		objTimeout.tv_usec = 100;
		objTimeout.tv_sec = 0;

		int nResult = select(m_nNetHandlerCount , pFdSetReads , pFdSetWrites , pFdSetExcepts , &objTimeout);
		if (nResult > 0)
		{
			MapNetHandlersT::iterator iterHandlers = m_mapNetHandlers.begin();
			for (; iterHandlers != m_mapNetHandlers.end(); ++ iterHandlers)
			{
				BOOL  bClosed = FALSE;
				SOCKET socket = iterHandlers->second->GetSocket(); 
				INetHandler * pNetHandler = iterHandlers->second;

				if (FD_ISSET(socket , pFdSetReads))
				{
					bClosed = pNetHandler->OnMsgRecving() <= 0 || bClosed;
				}

				if (FD_ISSET(socket , pFdSetWrites))
				{
					bClosed = pNetHandler->OnMsgSending() <= 0 || bClosed;
				}

				if (FD_ISSET(socket , pFdSetExcepts))
				{
					bClosed = TRUE;
				}

				ISession * pSession = pNetHandler->GetSession();
				if (pSession && pSession->GetObjTimeout().IsExpired() || pSession->GetClosed())
				{
					bClosed = TRUE;
				}

				if (bClosed)
				{
					DelNetHandler(pNetHandler);
				}  
			}
		} 

		return NET_ERROR_SUCCESS;
	}

	INT32 NetReactorSelect::AddNetHandler( INetHandler * pNetHandler , ENetHandlerFuncMask objMask /*= NET_FUNC_DEFAULT*/ )
	{
		Assert_Re(m_unMaxConnectionCount > m_nNetHandlerCount , -1);
	
		INT32  nFDMask = 0; 
		if(objMask & NET_FUNC_READ) 
			nFDMask |= FD_READ;
		if(objMask & NET_FUNC_WRITE)  
			nFDMask |= FD_WRITE;
		if(objMask & NET_FUNC_ACCEPT)  
			nFDMask |= FD_ACCEPT;
		if(objMask & NET_FUNC_EXCEPT)  
			nFDMask |= FD_CLOSE; 

		pNetHandler->SetNetHandlerIndex(m_nNetHandlerCount);
		m_mapNetHandlers.insert(std::make_pair(m_nNetHandlerCount , pNetHandler));
		m_mapNetEvents.insert(std::make_pair(m_nNetHandlerCount , nFDMask));

		++m_nNetHandlerCount;
		return NET_ERROR_SUCCESS;
	}

	INT32 NetReactorSelect::DelNetHandler( INetHandler * pNetHandler )
	{
		if (pNetHandler)
		{
			pNetHandler->OnClose();
			MapNetHandlersT::iterator iter = m_mapNetHandlers.find(pNetHandler->GetNetHandlerIndex());
			if (iter != m_mapNetHandlers.end())
			{
				SAFE_DELETE(pNetHandler);
				m_mapNetHandlers.erase(iter);
			}
			else
				Assert_Re("cant find Net Handler\n" && 0 , NET_ERROR_FAILURE);

			MapNetEventsT::iterator iterEvents = m_mapNetEvents.find(pNetHandler->GetNetHandlerIndex());
			if (iterEvents != m_mapNetEvents.end())
			{
				m_mapNetEvents.erase(iterEvents);
			}
			else
				Assert_Re("cant find Net Handler\n" && 0 , NET_ERROR_FAILURE);

			--m_nNetHandlerCount;
		}

		return NET_ERROR_SUCCESS;
	}

	INT32 NetReactorSelect::ModNetHandler( INetHandler * pNetHandler , ENetHandlerFuncMask objMask )
	{
		MapNetEventsT::iterator iterEvents = m_mapNetEvents.find(pNetHandler->GetNetHandlerIndex());
		if (iterEvents != m_mapNetEvents.end())
		{
			iterEvents->second = objMask;
		}
		else
			return  NET_ERROR_FAILURE;

		return NET_ERROR_SUCCESS;
	}


}