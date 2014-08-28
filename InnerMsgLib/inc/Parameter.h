#ifndef __msg_parameter_h__
#define __msg_parameter_h__ 

namespace Msg
{ 
	//5 ��������.��Ҫ���⼸��.�����Ĳ������Ϳ��Ը��������ȡģ���ػ��ķ�ʽ����ת��.
	enum PARAMETER_TYPE
	{ 
		PARAMETER_TYPE_ERROR  = 0 ,
		PARAMETER_TYPE_INT32  = 1 , 
		PARAMETER_TYPE_INT64  = 2 , 
		PARAMETER_TYPE_DOUBLE = 3 ,
		PARAMETER_TYPE_STRING = 4 ,
		PARAMETER_TYPE_CHUNK  = 5 ,
	};

	struct Parameter
	{
	public:
		Parameter()
			: m_unParamSize(0)
			, m_unParamType(PARAMETER_TYPE_ERROR)
		{
			value_BUF = NULL;
		}
		virtual ~Parameter()
		{
			if ((PARAMETER_TYPE_STRING == m_unParamType ||
				 PARAMETER_TYPE_CHUNK == m_unParamType) &&
				 value_BUF != NULL)
			{
				SAFE_DELETE(value_BUF);
			}
		}

	public:
		UINT32     GetSize(){ return m_unParamSize; }
		void       SetSize(UINT32 unParamSize){ m_unParamSize = unParamSize;}
		UINT32     GetType(){ return m_unParamType; }
		void       SetType(UINT32 unParamType){ m_unParamType = unParamType; }

		union
		{
			INT32  value_INT32;
			INT64  value_INT64;
			double value_DOUBLE;
			char * value_BUF;           //5 ������Ҫ��Chunk��char*������.
		};

	private:
		UINT32     m_unParamSize;         //5 �����Ĵ�С  
		UINT32     m_unParamType;         //5 ����������.��ӦPARAMETER_TYPE

	};

}
#endif