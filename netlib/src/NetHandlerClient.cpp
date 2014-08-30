#include "NetHandlerClient.h"
#include "NetHelper.h"

namespace Net
{   
	 INT32  NetHandlerClient::HandleMsg( UINT32 unMsgID, const char* pBuffer, UINT32 unLength )
	{
		return m_pMsgProcess->Process(unMsgID , pBuffer , unLength);
	}

	 INT32 NetHandlerClient::Init( const char* ip,int port )
	 { 
		 SOCKET socket = ::socket(AF_INET , SOCK_STREAM , 0);
		 SetSocket(socket);
		 return Connect(ip , port);
	 }

	 INT32 NetHandlerClient::Cleanup()
	 { 
		 closesocket(GetSocket());
		 return TRUE;
	 }

	 INT32 NetHandlerClient::Connect( const char* ip,int port )
	 {
		 {
			 int aio = 0;
			 NetHelper::SetIOCtrl(GetSocket() , FIONBIO , &aio);
		 }

		 sockaddr_in addr = {0};
		 addr.sin_family = AF_INET;
		 addr.sin_port = htons(port);
		 NetHelper::NetToN(ip , &addr.sin_addr);

		 int result =  ::connect(GetSocket(),(sockaddr*)&addr,sizeof(addr));

		 {
			 int aio = 1;
			 NetHelper::SetIOCtrl(GetSocket() , FIONBIO , &aio);
		 } 

		 return TRUE;
	 }

	 INT32 NetHandlerClient::OnClose()
	 {
		 return Cleanup();
	 }

}