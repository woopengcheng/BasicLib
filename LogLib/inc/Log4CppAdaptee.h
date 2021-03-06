#ifndef __log_log4cpp_interface_h__
#define __log_log4cpp_interface_h__ 
#include "LogCommon.h"    
#include "log4cpp/CategoryStream.hh"
#include "LogAdapter.h"
 
namespace Log
{  
	class DLL_EXPORT  Log4CppAdaptee : public LogAdapter
	{
	public:
		Log4CppAdaptee() {}
		virtual ~Log4CppAdaptee(){} 
			
	public: 
		virtual  UINT32  Init(const char * pLogName , const char * pLayoutConfig = NULL , BOOL bMultCategory = TRUE) ; 
		virtual  UINT32  Cleanup( void ); 

	public:
		virtual  void    Debug( std_ostream & os); 
		virtual  void    Error( std_ostream & os); 
		virtual  void    Warning( std_ostream & os); 
		virtual  void    Trace( std_ostream & os); 
		virtual  void    Other( std_ostream & os); 

	private:
//		virtual  log4cpp::CategoryStream  GetLog(LOG_TYPE logType ); 
		virtual  UINT32 CreateLog(const char * pName , const char * pLayoutConfig ,const char * pFile); 
	};
} 

#endif