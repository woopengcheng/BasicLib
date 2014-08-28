#include "ISession.h"

namespace Net
{ 
	INT32 ISession::ms_nSessionCount = 0;

	INT32 ISession::OnStart(char * pIP , UINT16 usPort)
	{
		memcpy(m_szSocketIP , pIP , strlen(pIP) + 1);
		m_usSocktPort = usPort;
		m_nSessionID = ++ISession::ms_nSessionCount;

		m_objTimeout.Start(DEFAULT_SESSION_TIME_OUT);
		return TRUE;
	}

	INT32 ISession::OnRecvMsg( void )
	{
		m_objTimeout.ResetTime();
		return TRUE;
	}

	INT32 ISession::OnSendMsg( void )
	{

		m_objTimeout.ResetTime();
		return TRUE;
	}

	INT32 ISession::OnClose( void )
	{
		m_objTimeout.Clean();
		return TRUE;
	}

}