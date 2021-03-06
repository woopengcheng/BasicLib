#include "TimerHelp.h"
#include "GlobalTimer.h"

namespace Timer
{  
#ifdef WIN32
	INT64 TimerHelper::GetTickCount()
	{  
		INT64  llCount = 0;
		QueryPerformanceCounter((LARGE_INTEGER *)(&llCount));

		return llCount;
	}

	INT64 TimerHelper::GetTickFrequency()
	{
		static INT64  s_llFrequency = 0;
		if (!s_llFrequency)
		{
			QueryPerformanceFrequency((LARGE_INTEGER *)(&s_llFrequency));
		}

		return s_llFrequency;
	} 
#else
	INT64 TimerHelper::GetTickCount()
	{ 
		timespec t;
		::clock_gettime(CLOCK_MONOTONIC,&t);              //5 CLOCK_REALTIME不同.这个是过去的某个逝去的时间点的次数.
		return (INT64)t.tv_sec * TIME_PRECISE + t.tv_nsec / (1e9 / TIME_PRECISE);   //5 微妙级别

		return llCount;
	}

	INT64 TimerHelper::GetTickFrequency()
	{  
		return TIME_PRECISE;
	}  
#endif

	INT64 TimerHelper::GetMilliSecond( INT64 llTime )
	{
		return llTime * GetTickFrequency() / 1000000;

	}

	INT64 TimerHelper::GetMicroSecond( INT64 llTime )
	{
		return llTime * GetTickFrequency() / 1000;
	}

	INT64 TimerHelper::GetSecond( INT64 llTime )
	{
		return llTime * GetTickFrequency();
	}

	INT64 TimerHelper::DiffMilliSecond( INT64 llTime1 , INT64 llTime2 )
	{
		return (llTime1 - llTime2) * 1000000 / GetTickFrequency(); 
	}

	INT64 TimerHelper::DiffMicroSecond( INT64 llTime1 , INT64 llTime2 )
	{
		return (llTime1 - llTime2) * 1000 / GetTickFrequency(); 

	}

	INT64 TimerHelper::DiffSecond( INT64 llTime1 , INT64 llTime2 )
	{
		return (llTime1 - llTime2) / GetTickFrequency(); 
	}

	std::string TimerHelper::GetDate(std::string strFormat/* = "%Y-%m-%d"*/)
	{
		time_t t = time(0); 
		char tmp[64]; 
		strftime( tmp, sizeof(tmp), "%Y-%m-%d",localtime(&t) );  
		return std::string(tmp); 
	}

	void TimerHelper::sleep( INT64 llMillSec )
	{
#ifdef WIN32
		::Sleep((DWORD)llMillSec);
#else  
		struct timespec objTimeSpec;
		objTimeSpec.tv_sec = llMillSec / 1000;
		objTimeSpec.tv_nsec = (llMillSec % 1000) * 1000000L;
		::nanosleep (&objTimeSpec, 0);
#endif
	}


}