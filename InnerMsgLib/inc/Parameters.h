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
		// Qualifier: ���������ʹ��һ��Ҫ���ڶԲ����Ѿ�ģ�廯�˺�ʹ��.�����������ֻ��ȡ���в����Ĵ�С.���������������.
		//************************************
		UINT32     GetSize();
		UINT32     Copy(Parameters * pParam);

	public:
		UINT32     m_unParamSize;
		Parameter  m_aParameter[MSG_MAX_PARAMETER_NUMBER];
	};

}
#endif