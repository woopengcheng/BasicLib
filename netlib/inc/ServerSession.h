#ifndef __net_server_session_h__
#define __net_server_session_h__ 
#include "ISession.h"

namespace Net 
{  
	enum EServerState
	{
		SERVER_STATE_ERROR = 0 ,
		SERVER_STATE_LOSTED  ,   //5 Á¬½Ó¶ªÊ§
		SERVER_STATE_RUNNING ,     
	};

	class ServerSession : public ISession
	{
	public:
		ServerSession()
			: m_objServerState(SERVER_STATE_ERROR)
		{}
		virtual ~ServerSession(){}

	public:
		virtual void SetClosed(BOOL val) 
		{
			m_objServerState = SERVER_STATE_LOSTED;
			ISession::SetClosed( val ); 
		}

	protected:
		EServerState    m_objServerState;
	}; 

}

#endif
