#ifndef __log_log_interface_h__
#define __log_log_interface_h__
#include "LogAdapter.h"

namespace Log
{
	class LogInterface
	{
	public:
		LogInterface()
			: m_pLogAdapter(NULL)
		{}
		~LogInterface(){}

	public:
		virtual  UINT32  Init(const char * pLogName , const char * pLayoutConfig = NULL , BOOL bMultCategory = TRUE) ; 
		virtual  UINT32  Cleanup(); 

	public:
		static LogInterface & GetInstance(){ static LogInterface m_sLogInterface; return m_sLogInterface; }

	public:
		LogAdapter  * GetLogAdapter()
		{
			Assert_Re0(m_pLogAdapter && "Log has not Init().");
			return m_pLogAdapter; 
		}
	private:
		LogAdapter  * m_pLogAdapter;

	};  
} 
#endif 