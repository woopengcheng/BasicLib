#ifndef __msg_static_method_impl_helper_h__
#define __msg_static_method_impl_helper_h__ 
#include "MethodImpl.h" 
#include "ParaseMsgCall.h"

namespace Msg
{  
	class StaticMethodImplHelper 
	{
	public:
		template<typename Object , typename Func>
		static void CallFuncEntry(ParaseMsgCall<Object> * pPMC);   //5 静态方法函数的入口

	public: 
		template<typename Object >
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(std::vector<Object> , Object ));  //5 对于消息调用的是无参数的函数
		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , P8 , std::vector<Object> , Object ));   
		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , std::vector<Object> , Object ));
		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 >
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , P6 , std::vector<Object> , Object ));
		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , std::vector<Object> , Object ));
		template<typename Object , typename P1 , typename P2 , typename P3 , typename P4>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , std::vector<Object> , Object  ));
		template<typename Object , typename P1 , typename P2 , typename P3>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , std::vector<Object> , Object  ));
		template<typename Object , typename P1 , typename P2>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , std::vector<Object> , Object ));
		template<typename Object , typename P1>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,void (*func)(P1 , std::vector<Object> , Object ));
	};

	template<typename Object , typename Func>
	void StaticMethodImplHelper::CallFuncEntry( ParaseMsgCall<Object> * pPMC )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		StaticMethodImpl<Object , Func> * pFunc = (StaticMethodImpl<Object , Func> *)(pPMC->m_pMehtodImpl);

  		CallFunc<Object>(pPMC , pFunc->m_objFunc);       //5 这里会根据传递进来的函数找到对应的参数.
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , P8 , std::vector<Object> , Object ))
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
				ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
				ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
				ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
				ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
				ParameterHelper<P6>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[5]) ,
				ParameterHelper<P7>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[6]) ,
				ParameterHelper<P8>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[7]) ,
				vecTargets , objSrc);
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , std::vector<Object> , Object ) )
	{ 
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
				ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
				ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
				ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
				ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
				ParameterHelper<P6>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[5]) ,
				ParameterHelper<P7>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[6]) ,
				vecTargets , objSrc);
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 >
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , P6 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
				ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
				ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
				ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
				ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
				ParameterHelper<P6>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[5]) ,
				ParameterHelper<P7>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[6]) ,
				vecTargets , objSrc);
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4 , typename P5>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , P5 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
				ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
				ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
				ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
				ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
				vecTargets , objSrc);
	}

	template<typename Object , typename P1 , typename P2 , typename P3 , typename P4>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , P4 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
				ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
				ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
				ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
				vecTargets , objSrc);
	}

	template<typename Object , typename P1 , typename P2 , typename P3>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , P3 , std::vector<Object> , Object  ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
				ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
				ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
				vecTargets , objSrc);
	}

	template<typename Object , typename P1 , typename P2>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , P2 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename P1>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(P1 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]),
			vecTargets , objSrc);
	}

	template<typename Object>
	void StaticMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,void (*func)(std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(*func)(vecTargets , objSrc);
	}

}

#endif