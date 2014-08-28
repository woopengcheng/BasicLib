#include "NetReactorSelect.h"
#include "ServerSession.h"
#include "TimerHelp.h"
#include "NetHandlerListener.h"

class Server
{
public:
	Server()
		: m_pNetReactor(new Net::NetReactorSelect)
	{

	}
	~Server(){ SAFE_DELETE(m_pNetReactor); }

public:
	virtual INT32  Init();
	virtual INT32  Cleanup();
	virtual INT32  Update();

private:
	Net::INetReactor *  m_pNetReactor;
};