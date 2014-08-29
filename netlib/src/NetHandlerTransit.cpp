#include "NetHandlerTransit.h"
#include "NetHelper.h"
#include "ByteOrder.h"

#ifdef WIN32
#include "Winsock.h"
#endif

namespace Net
{
	NetHandlerTransit::NetHandlerTransit( ISession * pSession )
		: INetHandler(pSession)
	{
		m_objRecvBuf.Init(DEFAULT_CIRCLE_BUFFER_SIZE);
		m_objSendBuf.Init(DEFAULT_CIRCLE_BUFFER_SIZE); 
	}

	NetHandlerTransit::~NetHandlerTransit( void )
	{
		m_objSendBuf.Cleanup();
		m_objRecvBuf.Cleanup();
	}

	void NetHandlerTransit::SetSocket( SOCKET socket )
	{
		INT32 nRes = 0;
		if (socket > 0)
		{
			INT32 valtrue = 1;

			nRes = setsockopt(socket,IPPROTO_TCP,TCP_NODELAY,(char*)&valtrue,sizeof(valtrue));
			nRes = setsockopt(socket,SOL_SOCKET,SO_KEEPALIVE,(char*)&valtrue,sizeof(valtrue));

			int recvbuf = DEFAULT_SOCKET_BUFFER_SIZE;
			int sendbuf = DEFAULT_SOCKET_BUFFER_SIZE;
			nRes = setsockopt(socket,SOL_SOCKET,SO_SNDBUF,(char*)&sendbuf,sizeof(sendbuf));
			nRes = setsockopt(socket,SOL_SOCKET,SO_RCVBUF,(char*)&recvbuf,sizeof(recvbuf));

			INetHandler::SetSocket(socket);
		} 
		return ;
	}

	INT32 NetHandlerTransit::OnMsgRecving( void )
	{
		char szBuf[DEFAULT_CIRCLE_BUFFER_SIZE];  //5 这里比系统定义的大.应该能一次性接收完.

		SOCKET socket  = GetSocket();
		UINT32 unBufSize = sizeof(szBuf);
		UINT32 unMaxBufSize = sizeof(szBuf);

		do
		{
			unBufSize = NetHelper::RecvMsg(socket , szBuf , sizeof(szBuf));
			if( unBufSize <  0 && NetHelper::IsSocketEagain())
				return 0;
			if( unBufSize <= 0 )
				return NET_ERROR_FAILURE;

			int result = RecvToCircleBuffer( szBuf , unBufSize);
			if( result < 0 )
				return result;
		}while(0);

		return NET_ERROR_SUCCESS;
	}

	INT32 NetHandlerTransit::RecvToCircleBuffer( char * pBuf , UINT32 unSize )
	{
		if(m_objRecvBuf.GetSpace() > unSize)
		{
			if (m_pSession)
			{
				m_pSession->OnRecvMsg();
			} 

			m_objRecvBuf.PushBuffer(pBuf , unSize);
			ParaseRecvMsg();
		}
		else
		{
			Assert_Re(false && "buffer full." , NET_ERROR_FAILURE);  
			this->m_objRecvBuf.SkipBytes(m_objRecvBuf.GetDataLength());
			return -1;
		}
		return NET_ERROR_SUCCESS;
	}

	INT32 NetHandlerTransit::ParaseRecvMsg()
	{
		while(m_objRecvBuf.GetDataLength() > 0)
		{
			UINT32 unMsgLength = 0;
//			m_bIgnorePolicy = true;

			INT32 nRecvBuf = (size_t)m_objRecvBuf.TryGetBuffer((char*)&unMsgLength , sizeof(UINT32));

			if(nRecvBuf < sizeof(UINT32))
				Assert_Re(0 && "msg header failed." , -1);

//			Convert<UINT32>::ToHostOrder(unMsgLength);

			// 错误的包长,直接断开
			if(unMsgLength > MAX_MESSAGE_LENGTH || unMsgLength <= 0)
			{
				Assert_Re( 0 && "error package len ,discard connection " , -1);  
			}

			if(m_objRecvBuf.GetDataLength() < unMsgLength)
				return 1;

			char szBuf[MAX_MESSAGE_LENGTH];
			m_objRecvBuf.GetBuffer(szBuf , unMsgLength);

			// 将长度和消息id转化为本机字节顺序
			MsgHeader * pHeader = (MsgHeader*)szBuf;

			HandleMsg(pHeader->unMsgID , szBuf + sizeof(MsgHeader) , pHeader->unMsgLength);
// 			pwutils::Convert<uint32>::ToHostOrder(header->len);
// 			pwutils::Convert<uint32>::ToHostOrder(header->mid);
//
//			HandleIncomingMsg(szBuf,unMsgLength);
		}

		return NET_ERROR_SUCCESS;
	}

	INT32 NetHandlerTransit::OnMsgSending( void )
	{
		return FlushSendBuffer();
	}

	INT32 NetHandlerTransit::FlushSendBuffer( void )
	{
		BOOL   bWriteable = TRUE;
		INT32  nSendBytes = 0;

		if (m_pSession)
		{
			m_pSession->OnSendMsg();
		}

		while(true)
		{
			if(!m_objSendBuf.IsVaild() || m_objSendBuf.GetDataLength() <= 0 || !bWriteable)
				break;

			char   szBuf[DEFAULT_CIRCLE_BUFFER_SIZE];
			INT32  nLength = m_objSendBuf.TryGetBuffer(szBuf,sizeof(szBuf));

#ifndef WIN32
			INT32 nSendLength = ::send(GetSocket(),szBuf,nLength,MSG_DONTWAIT);
#else
			INT32 nSendLength = ::send(GetSocket(),szBuf,nLength,0);
#endif
			if( nSendLength > 0 )
			{
				nSendBytes += nSendLength;
				m_objSendBuf.SkipBytes(nSendLength);
			}
			else if(nSendLength < 0 && NetHelper::IsSocketEagain())
			{
				bWriteable = false;
				break;
			}
			else
			{
				this->OnClose();
				break;
			}
		}

		return nSendBytes;  
	} 

	INT32 NetHandlerTransit::SendMsg( const char * pBuf , UINT32 unSize )
	{ 
		if(m_objSendBuf.IsVaild() && m_objSendBuf.GetDataLength() > 0)
		{
			if(m_objSendBuf.GetSpace() > unSize)
			{
				m_objSendBuf.PushBuffer(pBuf , unSize);
				FlushSendBuffer();
			}
			else
			{
				FlushSendBuffer();

				if(m_objSendBuf.GetSpace() > unSize)
				{
					m_objSendBuf.PushBuffer(pBuf , unSize);
				}
				else if(m_objSendBuf.GetDataLength() == 0)
				{
					// 大于缓存区大小,则直接发送
					INT32 nSendBytes = Send(pBuf  , unSize);
					if( nSendBytes <= 0)
					{
						Assert_Re(" sendbuffer.length=0,direct send failed,discard=%d\n" , -1); 
					}
					else if(nSendBytes != unSize)
					{
						Assert_Re(" sendbuffer.length=0,len=%d sent=%d\n" , -1); 
					}

					return (nSendBytes > 0) ? nSendBytes : 0;
				}
				else
				{
					Assert_Re(" sendbuff not empty,discard len=%d\n" , -1);  
				}
			}
			return unSize;
		}

		return Send(pBuf , unSize);

	}

	INT32 NetHandlerTransit::Send( const char * pBuf , UINT32 unSize , INT32 nTrySendCount/* = -1*/)
	{ 
		UINT32 unTotalSendBytes = 0;

		if(nTrySendCount == -1)
			nTrySendCount = 0x7FFFFFFF;  //5 死循环最多发送次数.

		while((unSize > unTotalSendBytes) && nTrySendCount--)
		{
#ifdef WIN32
			int nSendBytes = ::send(GetSocket(),&pBuf[unTotalSendBytes] , unSize - unTotalSendBytes , 0);
#else
			int nSendBytes = ::send(GetSocket(),&pBuf[unTotalSendBytes] , unSize - unTotalSendBytes,MSG_DONTWAIT);
#endif
			if(nSendBytes > 0)
			{
				unTotalSendBytes += nSendBytes;
			}
			else if(nSendBytes < 0 && NetHelper::IsSocketEagain())
			{
				continue;
			}
			else
			{
				this->OnClose();
				break;
			}
		}
		return unTotalSendBytes;
	}

	INT32 NetHandlerTransit::HandleMsg( UINT32 unMsgID, const char* pBuffer, UINT32 unLength )
	{
		return TRUE;
	}

	INT32 NetHandlerTransit::OnClose( void )
	{ 
		if (m_pSession)
		{
			m_pSession->OnClose();
		} 
		closesocket(GetSocket());
		return NET_ERROR_SUCCESS;
	}

}

