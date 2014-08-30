#ifndef __net_net_handler_client_h__
#define __net_net_handler_client_h__ 
#include "NetHandlerTransit.h"
#include "MsgProcess.h"

namespace Net 
{  
	class NetHandlerClient :public NetHandlerTransit
	{
	public:
		NetHandlerClient(ISession * pSession , MsgProcess * pMsgProcess)
			: NetHandlerTransit(pSession)  
			, m_pMsgProcess(pMsgProcess)
		{ 
		}
		virtual ~NetHandlerClient(){} 

	public:
		virtual INT32  Init( const char* ip,int port );
		virtual INT32  Cleanup();
		virtual INT32  OnClose();

	public:
		virtual INT32 HandleMsg(UINT32 unMsgID, const char* pBuffer, UINT32 unLength);
		 
	private:
		INT32  Connect( const char* ip,int port );

    private: 
		MsgProcess * m_pMsgProcess;
	}; 

	DECLARE_BOOST_POINTERS(NetHandlerClient);
}

#endif


