#ifndef __thread_pool_thread_pool_h__
#define __thread_pool_thread_pool_h__
#include "ThreadCommon.h"
#include "pthread.h" 
#include <map>


namespace ThreadPool
{
	typedef void *(*thread_fun) (void *);
	typedef void (*FuncSigHandler)(int);

	extern void  SigHandler(INT32 nSigno);

	class ThreadTask; 
	
	class DLL_EXPORT ThreadPool
	{
	public:
		typedef tbb_queue<ThreadTask *>                                 QueueThreadTasksT;
		typedef tbb_queue<pthread_t>									QueueThreadsT;
		typedef tbb_hash_map<UINT32 /*priority*/, QueueThreadTasksT>    MapThreadTasksT;
		typedef tbb_unordered_map<UINT32 /*priority*/, UINT32 /*size*/> MapThreadPriorityCountT;
		
	public:
		ThreadPool(): m_bPirorityStrict(TRUE){}
		virtual ~ThreadPool(){}  
		  
	public:
		virtual BOOL Init(char * pFile = NULL);
		virtual BOOL Init(std::map<UINT32 , UINT32 > & mapPriorityCount , BOOL bStrict = TRUE);
		virtual BOOL Cleanup();
		virtual BOOL Startup(); 
		virtual BOOL Closeup();

	public:
		virtual BOOL         AddTask(ThreadTask * pThreadTask);
		virtual ThreadTask * FetchTask( UINT32 unThreadPriority); 
		virtual UINT32       GetThreadsCount();
		virtual BOOL         CreateThread(UINT32 unPriority , UINT32 unThreadCount = 1);
		virtual INT32        CreateThread(pthread_t & th , pthread_attr_t * attr ,thread_fun pFunc , void * pParam ); 
		 
	private:
		static void * ThreadFunc(void * pParam); 
		ThreadTask *  FetchLowerBoundTask( UINT32 unThreadPriority); 
		BOOL          HasPriorityThread(UINT32 unPriority);
		BOOL          KillChildrenThread();
		void          RegisterSig(int nSigno , FuncSigHandler  pSigHandler);

	private: 
		BOOL                    m_bPirorityStrict;        //5 初始化数据,初始化后不能修改,所以多线程安全.
		MapThreadPriorityCountT m_mapThreadPriorityCount; //5 初始化数据.
		MapThreadTasksT         m_mapThreadTasks;
		QueueThreadsT           m_queueThreads;
	};

}; 
#endif