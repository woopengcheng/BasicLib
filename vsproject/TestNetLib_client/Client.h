#include "NetReactorSelect.h"
#include "ISession.h"
#include "NetHandlerClient.h"
#include "TimerHelp.h"
#include "MsgProcess.h"

class TestMsgProcess : public Net::MsgProcess
{
public:
	virtual INT32 Process(UINT32 unMsgID, const char* pBuffer, UINT32 unLength);
};

class Client  
{
public:
	Client()
		: m_pNetReactor(new Net::NetReactorSelect)  
		, m_pMsgProcess(NULL)
	{

	}
	~Client(){  }

public:
	virtual INT32  Init();
	virtual INT32  Cleanup(); 
	virtual INT32  Update(); 

private:
	Net::INetReactor         *  m_pNetReactor;
	Net::NetHandlerClientPtr    m_pNetHandlerClient;
	Net::MsgProcess          *  m_pMsgProcess;
	//	Net::NetHandlerClient *  m_pNetHandlerClient;
};