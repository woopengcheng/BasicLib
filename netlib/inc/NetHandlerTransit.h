#ifndef __net_net_handler_transit_h__
#define __net_net_handler_transit_h__ 
#include "INetHandler.h"
#include "CircleBuffer.h"

namespace Net 
{  
	class NetHandlerTransit :public INetHandler
	{
	public:
		NetHandlerTransit(ISession * pSession); 
		virtual ~NetHandlerTransit( void );

	public:
		virtual INT32  OnMsgRecving( void ); 
		virtual INT32  OnMsgSending( void ); 
		virtual INT32  OnClose( void )     ;
		virtual void   SetSocket(SOCKET socket);

	public:                         
		virtual INT32  SendMsg( const char * pBuf , UINT32 unSize );
		virtual INT32  Send( const char * pBuf , UINT32 unSize , INT32 nTrySendCount = -1);
		virtual INT32  ParaseRecvMsg();     
		virtual INT32  RecvToCircleBuffer(char * pBuf , UINT32 unSize);   //5 将消息扔给CircleBuffer
		virtual INT32  HandleMsg(UINT32 unMsgID, const char* pBuffer, UINT32 unLength);

	private:
		INT32   FlushSendBuffer( void );

	private:
		Util::CircleBuffer    m_objSendBuf;
		Util::CircleBuffer    m_objRecvBuf;
	}; 
}

#endif


