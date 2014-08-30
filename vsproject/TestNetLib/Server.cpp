#include "Server.h"

INT32 Server::Init()
{
	if (!m_pNetReactor)
	{
		m_pNetReactor = new Net::NetReactorSelect;
	}
	m_pNetReactor->Init();

	Net::NetHandlerListenerPtr pNetHandlerListener(new Net::NetHandlerListener(m_pNetReactor , new Net::ISession));
	pNetHandlerListener->Init("127.0.0.1" , 5555);
	m_pNetReactor->AddNetHandler(pNetHandlerListener);

	return TRUE;
}

INT32 Server::Cleanup()
{
	return TRUE;
}

INT32 Server::Update()
{
	while(1)
	{
		m_pNetReactor->Update();
		Timer::TimerHelper::sleep(1); 
	}
	return TRUE;
}
