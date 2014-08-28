#ifndef __msg_process_CB01E0E3_A628_4DF5_B658_513E8056BAA3_h__
#define __msg_process_CB01E0E3_A628_4DF5_B658_513E8056BAA3_h__
#include "MsgProcess.h"
#include "Common.h"
#include "accsrv.pb.h"

namespace Game
{
	class GameMsgProcess: public Net::MsgProcess
	{
	public:
		virtual BOOL IsAccept(UINT32 unMsgID) { return true; }

	public:
		GameMsgProcess(){}
		virtual ~GameMsgProcess(){}

	public:
		virtual INT32 Process(UINT32 unMsgID, const char* pBuffer, UINT32 unLength);
	public:
		INT32 Process(::Net::accsrv::CSLogin & msg);// msgid:1 name:CSLogin
	};
} //::Net::accsrv

#endif // __msg_process_CB01E0E3_A628_4DF5_B658_513E8056BAA3_h__
