#ifndef __msg_parameters_h__
#define __msg_parameters_h__ 
#include "MsgCommon.h"
#include "Parameter.h"

namespace Msg
{ 
	class  Parameters
	{
	public: 
		Parameters() : m_unParamSize(0){}
		~Parameters(){}

	public:
		//************************************
		// Method:    GetSize
		// FullName:  Msg::Parameters::GetSize
		// Access:    public 
		// Returns:   UINT32
		// Qualifier: 这个函数的使用一定要放在对参数已经模板化了后使用.并且这个参数只获取所有参数的大小.不包括本身的数据.
		//************************************
		UINT32     GetSize();
		UINT32     Copy(Parameters * pParam);

	public:
		UINT32     m_unParamSize;
		Parameter  m_aParameter[MSG_MAX_PARAMETER_NUMBER];
	};

}
#endif