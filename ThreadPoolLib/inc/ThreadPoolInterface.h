#ifndef __thread_pool_thread_pool_interface_h__
#define __thread_pool_thread_pool_interface_h__ 
#include "ThreadPool.h"

namespace ThreadPool
{ 

	class DLL_EXPORT ThreadPoolInterface : public ThreadPool
	{ 
	public:	
		static ThreadPoolInterface & GetInstance() { static ThreadPoolInterface m_sInstance; return m_sInstance;} 
	};

};
 
#endif