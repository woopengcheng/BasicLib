#ifndef __msg_gen_msg_helper_h__
#define __msg_gen_msg_helper_h__ 
#include "MsgCommon.h"
#include "ParameterHelper.h"
#include "ObjectMsgCall.h"

namespace Msg
{
	class GenMsgHelper
	{ 
	public: 
		template<typename Object>
		static BOOL GenMsgCall(ObjectMsgCall<Object> & objMsgCall , UINT32 unMsgID , const char * pMsgCallName , UINT16 usPriority = 0);

		template<typename Object>
		static BOOL GenMsgCall(ObjectMsgCall<Object> & objMsgCall , UINT32 unMsgID , const char * pMsgCallName , std::vector<Object> & vtTargets , Object objSrc , UINT16 usPriority = 0);

		template<typename Object>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall);

		template<typename Object , typename P1>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1);

		template<typename Object , typename P1 , typename P2>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2);

		template<typename Object , typename P1 , typename P2 , typename P3>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3);

		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4);

		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5);

		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 , P6 &p6);

		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 , P6 &p6 , P7 &p7);

		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8>
		static void GenMsgParams(ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 , P6 &p6 , P7 &p7 , P8 &p8);

	};

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 , P6 &p6 , P7 &p7 , P8 &p8 )
	{
		objMsgCall.m_objParams.m_unParamSize = 8;
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
		ParameterHelper<P3>::MakeParameter(objMsgCall.m_objParams.m_aParameter[2] , p3); 
		ParameterHelper<P4>::MakeParameter(objMsgCall.m_objParams.m_aParameter[3] , p4); 
		ParameterHelper<P5>::MakeParameter(objMsgCall.m_objParams.m_aParameter[4] , p5); 
		ParameterHelper<P6>::MakeParameter(objMsgCall.m_objParams.m_aParameter[5] , p6); 
		ParameterHelper<P7>::MakeParameter(objMsgCall.m_objParams.m_aParameter[6] , p7); 
		ParameterHelper<P8>::MakeParameter(objMsgCall.m_objParams.m_aParameter[7] , p8); 
	}


	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 , P6 &p6 , P7 &p7 )
	{
		objMsgCall.m_objParams.m_unParamSize = 7; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
		ParameterHelper<P3>::MakeParameter(objMsgCall.m_objParams.m_aParameter[2] , p3); 
		ParameterHelper<P4>::MakeParameter(objMsgCall.m_objParams.m_aParameter[3] , p4); 
		ParameterHelper<P5>::MakeParameter(objMsgCall.m_objParams.m_aParameter[4] , p5); 
		ParameterHelper<P6>::MakeParameter(objMsgCall.m_objParams.m_aParameter[5] , p6); 
		ParameterHelper<P7>::MakeParameter(objMsgCall.m_objParams.m_aParameter[6] , p7); 
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 , P6 &p6 )
	{
		objMsgCall.m_objParams.m_unParamSize = 6; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
		ParameterHelper<P3>::MakeParameter(objMsgCall.m_objParams.m_aParameter[2] , p3); 
		ParameterHelper<P4>::MakeParameter(objMsgCall.m_objParams.m_aParameter[3] , p4); 
		ParameterHelper<P5>::MakeParameter(objMsgCall.m_objParams.m_aParameter[4] , p5); 
		ParameterHelper<P6>::MakeParameter(objMsgCall.m_objParams.m_aParameter[5] , p6); 
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 , P5 &p5 )
	{
		objMsgCall.m_objParams.m_unParamSize = 5; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
		ParameterHelper<P3>::MakeParameter(objMsgCall.m_objParams.m_aParameter[2] , p3); 
		ParameterHelper<P4>::MakeParameter(objMsgCall.m_objParams.m_aParameter[3] , p4); 
		ParameterHelper<P5>::MakeParameter(objMsgCall.m_objParams.m_aParameter[4] , p5); 
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 , P4 &p4 )
	{
		objMsgCall.m_objParams.m_unParamSize = 4; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
		ParameterHelper<P3>::MakeParameter(objMsgCall.m_objParams.m_aParameter[2] , p3); 
		ParameterHelper<P4>::MakeParameter(objMsgCall.m_objParams.m_aParameter[3] , p4);  
	}

	template<typename Object , typename P1 , typename P2 , typename P3>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 , P3 &p3 )
	{
		objMsgCall.m_objParams.m_unParamSize = 3; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
		ParameterHelper<P3>::MakeParameter(objMsgCall.m_objParams.m_aParameter[2] , p3); 
	}

	template<typename Object , typename P1 , typename P2>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 , P2 &p2 )
	{
		objMsgCall.m_objParams.m_unParamSize = 2; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
		ParameterHelper<P2>::MakeParameter(objMsgCall.m_objParams.m_aParameter[1] , p2); 
	}

	template<typename Object , typename P1>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall , P1 &p1 )
	{
		objMsgCall.m_objParams.m_unParamSize = 1; 
		ParameterHelper<P1>::MakeParameter(objMsgCall.m_objParams.m_aParameter[0] , p1);
	}

	template<typename Object>
	void GenMsgHelper::GenMsgParams( ObjectMsgCall<Object> & objMsgCall )
	{
		objMsgCall.m_objParams.m_unParamSize = 0; 
	}

	template<typename Object>
	BOOL GenMsgHelper::GenMsgCall( ObjectMsgCall<Object> & objMsgCall , UINT32 unMsgID , const char * pMsgCallName , std::vector<Object> & vtTargets , Object objSrc  , UINT16 usPriority )
	{
		objMsgCall.m_unMsgID = unMsgID;
		objMsgCall.m_objSource = objSrc;
		objMsgCall.m_usPriority = usPriority;

		if (vtTargets.size() == 0)
		{
			return FALSE;
		} 

		objMsgCall.m_unTargetsCount = vtTargets.size();
		std::vector<Object>::iterator iter = vtTargets.begin();
		for (UINT32 i = 0 ;iter != vtTargets.end();++iter , ++i)
		{
			objMsgCall.m_aTargets[i] = *iter; 
		}

		memcpy(objMsgCall.m_szMsgMethod , pMsgCallName , MAX_MSG_METHOD_NAME_LENGTH); 

		return TRUE;
	} 

	template<typename Object>
	BOOL GenMsgHelper::GenMsgCall( ObjectMsgCall<Object> & objMsgCall , UINT32 unMsgID , const char * pMsgCallName , UINT16 usPriority)
	{
		objMsgCall.m_unMsgID = unMsgID;   
		objMsgCall.m_usPriority = usPriority;

		memcpy(objMsgCall.m_szMsgMethod , pMsgCallName , MAX_MSG_METHOD_NAME_LENGTH); 

		return TRUE;
	} 
}

#endif