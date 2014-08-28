#include "LogInterface.h" 
#include "Log4CPlusAdaptee.h"
#include "Log4CppAdaptee.h"
#include "log4cplus/loggingmacros.h"
#include "GLogAdaptee.h"

namespace Log
{   
	std::string g_strLogTypeName[MAX_LOG_TYPE] = {"debug" , "error" , "warning" , "trace" , "others" , "all"};
 
	UINT32 LogInterface::Init( const char * pLogName , const char * pLayoutConfig /*= NULL */, BOOL bMultCategory /*= TRUE*/ )
	{
#ifdef USE_LOG4CPP
		m_pLogAdapter = new Log4CppAdaptee; 
#elif defined USE_LOG4CPLUS
		m_pLogAdapter = new Log4CPlusAdaptee;
#elif defined USE_GLOG
		m_pLogAdapter = new GLogAdaptee;
#endif

		return m_pLogAdapter->Init(pLogName , pLayoutConfig , bMultCategory);
	}

	UINT32 LogInterface::Cleanup()
	{
		if (m_pLogAdapter)
		{ 
			m_pLogAdapter->Cleanup();
			SAFE_DELETE(m_pLogAdapter);
			return TRUE;
		}
		return  FALSE;
	}

}