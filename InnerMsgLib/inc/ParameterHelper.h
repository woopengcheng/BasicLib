#ifndef __msg_parameter_helper_h__
#define __msg_parameter_helper_h__
#include "MsgCommon.h"
#include "Parameter.h"
#include "Chunk.h"

namespace Msg 
{ 

	template<typename T>
	class ParameterHelper
	{

	};

	template<> class ParameterHelper<const char *>
	{
	public:
		static PARAMETER_TYPE GetParameterType()
		{
			return PARAMETER_TYPE_STRING;
		}

		static const char * GetParameterValue(Parameter & objParam)
		{
			switch (objParam.GetType())
			{
			case PARAMETER_TYPE_CHUNK:
			case PARAMETER_TYPE_STRING:
				{
					return objParam.value_BUF;
				}
				break;
			default:
				Assert_Re0(false && "invalid convert to const char*");
			}

			return NULL;
		}

		static void MakeParameter(Parameter & objParam , const char * pValue)
		{ 
			UINT32 unSize = (UINT32)strlen(pValue) + 1;
			objParam.SetSize(unSize);
			objParam.SetType(PARAMETER_TYPE_STRING);
			 
			objParam.value_BUF = new char[unSize];
			memcpy(objParam.value_BUF , pValue , unSize); 
		}
	};

	template<> class ParameterHelper<Chunk>
	{
	public:
		static PARAMETER_TYPE GetParameterType()
		{
			return PARAMETER_TYPE_CHUNK;
		}

		static Chunk GetParameterValue(Parameter & objParam)
		{
			Chunk objChunk;
			switch (objParam.GetType())
			{
			case PARAMETER_TYPE_CHUNK: 
				{
					objChunk.SetSize(objChunk.GetSize());
					objChunk.SetBuf(objParam.value_BUF);
					return objChunk;
				}
				break;
			default:
				Assert_Re(false && "invalid convert to Chunk" , objChunk);
			}

			return objChunk;
		}

		static void MakeParameter(Parameter & objParam , Chunk pValue)
		{ 
			objParam.SetSize(pValue.GetSize());
			objParam.SetType(PARAMETER_TYPE_CHUNK);

			objParam.value_BUF = new char[pValue.GetSize()]; 
			memcpy(objParam.value_BUF , pValue.GetBuf() , pValue.GetSize());  
		}
	};

	template<> class ParameterHelper<INT32>
	{
	public:
		static PARAMETER_TYPE GetParameterType()
		{
			return PARAMETER_TYPE_INT32;
		}

		static INT32 GetParameterValue(Parameter & objParam)
		{ 
			switch (objParam.GetType())
			{
			case PARAMETER_TYPE_INT32: 
				{ 
					return objParam.value_INT32;
				}
				break; 
			default:
				Assert_Re(false && "invalid convert to INT32" , -1);
			}

			return -1;
		}

		static void MakeParameter(Parameter & objParam , INT32 nValue)
		{ 
			objParam.SetSize(0);
			objParam.SetType(PARAMETER_TYPE_INT32);
			objParam.value_INT32 = nValue;
		}
	};

	template<> class ParameterHelper<bool>
	{
	public:
		static PARAMETER_TYPE GetParameterType()
		{
			return PARAMETER_TYPE_INT32;
		}

		static bool GetParameterValue(Parameter & objParam)
		{ 
			switch (objParam.GetType())
			{
			case PARAMETER_TYPE_INT32: 
				{ 
					return objParam.value_INT32 == 1;
				}
				break; 
			default:
				Assert_Re0(false && "invalid convert to bool");
			}

			return false;
		}

		static void MakeParameter(Parameter & objParam , bool bValue)
		{ 
			objParam.SetSize(0);
			objParam.SetType(PARAMETER_TYPE_INT32);
			objParam.value_INT32 = bValue;
		}
	};

	template<> class ParameterHelper<INT64>
	{
	public:
		static PARAMETER_TYPE GetParameterType()
		{
			return PARAMETER_TYPE_INT64;
		}

		static INT64 GetParameterValue(Parameter & objParam)
		{ 
			switch (objParam.GetType())
			{ 
			case PARAMETER_TYPE_INT64: 
				{ 
					return objParam.value_INT64;
				}
				break; 
			default:
				Assert_Re(false && "invalid convert to INT64" , -1);
			}

			return -1;
		}

		static void MakeParameter(Parameter & objParam , INT64 nValue)
		{ 
			objParam.SetSize(0);
			objParam.SetType(PARAMETER_TYPE_INT64);
			objParam.value_INT64 = nValue;
		}
	};


	template<> class ParameterHelper<double>
	{
	public:
		static PARAMETER_TYPE GetParameterType()
		{
			return PARAMETER_TYPE_DOUBLE;
		}

		static double GetParameterValue(Parameter & objParam)
		{ 
			switch (objParam.GetType())
			{ 
			case PARAMETER_TYPE_DOUBLE: 
				{ 
					return objParam.value_DOUBLE;
				}
				break; 
			default:
				Assert_Re(false && "invalid convert to double" , 0.0f);
			}

			return 0.0f;
		}

		static void MakeParameter(Parameter & objParam , double dValue)
		{ 
			objParam.SetSize(0);
			objParam.SetType(PARAMETER_TYPE_DOUBLE);
			objParam.value_DOUBLE = dValue;
		}
	};

	template<> struct ParameterHelper<char> : public ParameterHelper<INT32> {};
	template<> struct ParameterHelper<INT16> : public ParameterHelper<INT32> {};
	template<> struct ParameterHelper<UINT16> : public ParameterHelper<INT32> {}; 
	template<> struct ParameterHelper<UINT32> : public ParameterHelper<INT32> {};
	template<> struct ParameterHelper<long> : public ParameterHelper<INT64> {}; 
	template<> struct ParameterHelper<UINT64> : public ParameterHelper<INT64> {}; 
}

#endif
