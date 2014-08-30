#ifndef __net_i_net_handler_h__
#define __net_i_net_handler_h__ 
#include "NetCommon.h"
#include "ISession.h"

namespace Net 
{  
	class DLL_EXPORT INetHandler
	{
	public:
		INetHandler( ISession * pSession )
			: m_unNetHandlerIndex(0) 
			, m_socket(0)
			, m_pSession(pSession)
		{}
		virtual ~INetHandler( void )
		{ 
		} 

	public:
		virtual INT32  OnMsgRecving( void ) { return 0; }
		virtual INT32  OnMsgSending( void ) { return 0; }  
		virtual INT32  OnClose( void )      { return 0; }
		virtual void   SetSocket(SOCKET val) { m_socket = val; }

	public:
		SOCKET GetSocket( void ) const { return m_socket; }
		UINT32 GetNetHandlerIndex( void ) const { return m_unNetHandlerIndex; }
		void   SetNetHandlerIndex(UINT32 val) { m_unNetHandlerIndex = val; }
		ISession * GetSession(){ return m_pSession; }

	protected:
		SOCKET         m_socket; 
		UINT32         m_unNetHandlerIndex;
		ISession    *  m_pSession;             //5 session 交给Net自动管理.所以一定要new出来.
	}; 

	DECLARE_BOOST_POINTERS(INetHandler);
}

#endif
