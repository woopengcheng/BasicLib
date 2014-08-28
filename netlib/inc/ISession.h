#ifndef __net_i_session_h__
#define __net_i_session_h__ 
#include "NetCommon.h"
#include "TimeCount.h"

namespace Net 
{  
	class ISession
	{
	public:
		ISession( void )
			: m_nSessionID(-1) 
			, m_bClosed(FALSE)
		{

		}
		virtual ~ISession( void ){}

	public:
		virtual    INT32   OnStart(char * pIP , UINT16 usPort);
		virtual    INT32   OnRecvMsg( void );
		virtual    INT32   OnSendMsg( void );
		virtual    INT32   OnClose( void );
		 
	public:
		INT32 GetSessionID() const { return m_nSessionID; }
		void SetSessionID(INT32 val) { m_nSessionID = val; }
		UINT16 GetSocktPort() const { return m_usSocktPort; }
		void SetSocktPort(UINT16 val) { m_usSocktPort = val; }
		char * GetSocketIP() { return m_szSocketIP; }
		void SetSocketIP(char * val) { memcpy(m_szSocketIP , val ,strlen(val)); }
		Timer::TimeCount GetObjTimeout() const { return m_objTimeout; }
		void SetObjTimeout(Timer::TimeCount val) { m_objTimeout = val; }
		BOOL GetClosed() const { return m_bClosed; }
		virtual void SetClosed(BOOL val) { m_bClosed = val; }

	protected:
		BOOL              m_bClosed;
		INT32			  m_nSessionID;
		UINT16            m_usSocktPort;
		char		      m_szSocketIP[MAX_NAME_LENGTH];
		Timer::TimeCount  m_objTimeout;

	public:
		static   INT32    ms_nSessionCount; 
	}; 

}

#endif
