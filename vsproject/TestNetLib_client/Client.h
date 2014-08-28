#include "NetReactorSelect.h"
#include "ServerSession.h"
#include "NetHandlerClient.h"
#include "TimerHelp.h"

class Client : public Net::NetHandlerClient
{
public:
	Client()
		: m_pNetReactor(new Net::NetReactorSelect)
		, NetHandlerClient(new Net::ServerSession)
	{

	}
	~Client(){ SAFE_DELETE(m_pNetReactor); }

public:
	virtual INT32  Init();
	virtual INT32  Cleanup(); 
	virtual INT32  Update(); 

private:
	Net::INetReactor *  m_pNetReactor;
};