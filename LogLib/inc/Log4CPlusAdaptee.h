#ifndef __log_log4cplus_adaptee_h__
#define __log_log4cplus_adaptee_h__ 
#include "log4cplus/logger.h"
#include "LogAdapter.h"
 
namespace Log
{    
	class DLL_EXPORT Log4CPlusAdaptee : public LogAdapter
	{
	public:
		Log4CPlusAdaptee() {}
		virtual ~Log4CPlusAdaptee(){} 

	public: 
		virtual  UINT32  Init(const char * pLogName , const char * pLayoutConfig = NULL , BOOL bMultCategory = TRUE) ; 
		virtual  UINT32  Cleanup(); 

	public:
		virtual  void    Debug( std_ostream & os ); 
		virtual  void    Error( std_ostream & os); 
		virtual  void    Warning( std_ostream & os); 
		virtual  void    Trace( std_ostream & os); 
		virtual  void    Other( std_ostream & os); 

	public: 
		virtual  UINT32				CreateLog(const char * pName , const char * pLayoutConfig , const char * pFile);
//		virtual  log4cplus::Logger  GetLog(LOG_TYPE logType);  
	};

} 
#endif