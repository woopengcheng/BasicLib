#include "Client.h"

INT32 Client::Init()
{
	if (!m_pNetReactor)
	{
		m_pNetReactor = new Net::NetReactorSelect;
	}
	m_pNetReactor->Init();
	 
	NetHandlerClient::Init("127.0.0.1" , 5555);
	m_pNetReactor->AddNetHandler(this);

	return TRUE;
}

INT32 Client::Cleanup()
{
	return TRUE;
}

INT32 Client::Update()
{
	while(1)
	{
		m_pNetReactor->Update();

		char pBuf[1024]; 
		((Net::MsgHeader*)pBuf)->unMsgID = 0;
		((Net::MsgHeader*)pBuf)->unMsgLength = 6+ sizeof(Net::MsgHeader);
		memcpy(pBuf + sizeof(Net::MsgHeader) , "asdfa" , 6);
		SendMsg(pBuf , 6 + sizeof(Net::MsgHeader));
		Timer::TimerHelper::sleep(1); 
	}
	return TRUE;
}

