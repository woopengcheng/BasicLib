#include "Parameters.h"

namespace Msg
{ 
	UINT32 Parameters::GetSize()
	{
		UINT32 unResult = 0;
		for (UINT32 i = 0;i < m_unParamSize;++i)
		{
			unResult += m_aParameter[i].GetSize();
		}

		return unResult;
	}

	UINT32 Parameters::Copy( Parameters * pParam )
	{
		pParam->m_unParamSize = m_unParamSize;

		for (UINT32 i = 0;i < m_unParamSize;++i)
		{
			switch(m_aParameter[i].GetType())
			{
			case PARAMETER_TYPE_INT32:
				{
					pParam->m_aParameter[i].value_INT32 = m_aParameter[i].value_INT32;
				}break;
			case PARAMETER_TYPE_INT64:
				{
					pParam->m_aParameter[i].value_INT64 = m_aParameter[i].value_INT64;
				}break;
			case PARAMETER_TYPE_DOUBLE:
				{
					pParam->m_aParameter[i].value_DOUBLE = m_aParameter[i].value_DOUBLE;
				}break;
			case PARAMETER_TYPE_CHUNK:
			case PARAMETER_TYPE_STRING:
				{
					pParam->m_aParameter[i].value_BUF = new char[m_aParameter[i].GetSize()];
					memcpy(pParam->m_aParameter[i].value_BUF , m_aParameter[i].value_BUF , m_aParameter[i].GetSize());
				}break; 
			default:
				break;
			} 
		} 

		return TRUE;
	}

}