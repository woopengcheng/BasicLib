// TestNetLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"  
#include "ThreadPoolInterface.h"
#include "ThreadTask.h"  
#include "Server.h"

int _tmain(int argc, _TCHAR* argv[])
{   
#ifdef WIN32
	WSADATA wsd;
	WSAStartup(MAKEWORD(2,2),&wsd);
#endif

	int nCount = ThreadPool::ThreadPoolInterface::GetInstance().GetThreadsCount(); 
	Server server;
	server.Init();

	server.Update();


#ifdef _WIN32
	WSACleanup();
#endif
	return 0;
}

