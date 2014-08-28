#ifndef __msg_object_method_impl_helper_h__
#define __msg_object_method_impl_helper_h__ 
#include "MethodImpl.h" 
#include "ParaseMsgCall.h"

namespace Msg
{  
	class ObjectMethodImplHelper
	{
	public:
		template<typename Object , typename ClassObject , typename Func>
		static void CallFuncEntry(ParaseMsgCall<Object> * pPMC);   //5 类成员方法函数的入口

	public:
		template<typename Object , typename ClassObject>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)( std::vector<Object> , Object ));  //5 对于消息调用的是无参数的函数
		template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , P8 , std::vector<Object> , Object ));   
		template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , std::vector<Object> , Object ));
		template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 >
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , P6 , std::vector<Object> , Object ));
		template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , std::vector<Object> , Object ));
		template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , std::vector<Object> , Object ));
		template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , std::vector<Object> , Object ));
		template<typename Object , typename ClassObject , typename P1 , typename P2>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , std::vector<Object> , Object ));
		template<typename Object , typename ClassObject , typename P1>
		static void CallFunc(ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , std::vector<Object> , Object ));
	};

	template<typename Object , typename ClassObject , typename Func>
	void ObjectMethodImplHelper::CallFuncEntry( ParaseMsgCall<Object> * pPMC)
	{
		Assert(pPMC && pPMC->m_pMehtodImpl && pPMC->m_pMsgCall && pPMC->m_pObj);

		ClassObject * pObj = static_cast<ClassObject*>(pPMC->m_pObj); 
		  
		ObjectMethodImpl<Object , ClassObject , Func> * pMehtodImpl = static_cast<ObjectMethodImpl<Object , ClassObject , Func>*>(pPMC->m_pMehtodImpl);
		CallFunc<Object , ClassObject>(pPMC, *pObj , pMehtodImpl->m_objFunc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , P8 , std::vector<Object> , Object ))
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
			ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
			ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
			ParameterHelper<P6>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[5]) ,
			ParameterHelper<P7>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[6]) ,
			ParameterHelper<P8>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[7]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , P6 , P7 , std::vector<Object> , Object ) )
	{ 
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
			ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
			ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
			ParameterHelper<P6>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[5]) ,
			ParameterHelper<P7>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[6]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , P6  , std::vector<Object> , Object ) )
	{ 
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
			ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
			ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
			ParameterHelper<P6>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[5]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 >
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , P5 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
			ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
			ParameterHelper<P5>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[4]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3 , typename P4>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , P4 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
			ParameterHelper<P4>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[3]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2 , typename P3>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , P3 , std::vector<Object> , Object  ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			ParameterHelper<P3>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[2]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1 , typename P2>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , P2 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]) , 
			ParameterHelper<P2>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[1]) ,
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject , typename P1>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(P1 , std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(ParameterHelper<P1>::GetParameterValue(pPMC->m_pMsgCall->m_objParams.m_aParameter[0]),
			vecTargets , objSrc);
	}

	template<typename Object , typename ClassObject>
	void ObjectMethodImplHelper::CallFunc( ParaseMsgCall<Object> * pPMC,ClassObject & obj , void (ClassObject::*func)(std::vector<Object> , Object ) )
	{
		Assert(pPMC && pPMC->m_pMsgCall);
		std::vector<Object> vecTargets;
		for (UINT32 i = 0;i < pPMC->m_pMsgCall->m_unTargetsCount;++i)
		{
			vecTargets.push_back(pPMC->m_pMsgCall->m_aTargets[i]);
		}
		Object objSrc = pPMC->m_pMsgCall->m_objSource;

		(obj.*func)(vecTargets , objSrc);
	}

}

#endif