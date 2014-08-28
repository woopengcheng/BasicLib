#ifndef __msg_msg_dispatcher_h__
#define __msg_msg_dispatcher_h__
#include "MethodImpl.h"
#include "ParaseMsgCall.h" 
#include "StaticMethodImplHelper.h"
#include "ObjectMethodImplHelper.h"

namespace Msg 
{ 
	template<typename Object>
	class MsgDispatcher
	{
	public:
		MsgDispatcher(){}
		virtual ~MsgDispatcher();
	public:
		typedef  tbb_hash_map<std::string , MethodImpl<Object> *> MapMethodImplT;
		typedef  tbb_hash_map<Object , ICallableObject<Object> *> MapCallableObjectsT;

	public:
		INT32   AddCallableObject(ICallableObject<Object> * pCallableObject);
		INT32   DelCallableObject(ICallableObject<Object> * pCallableObject);

		MethodImpl<Object> *   GetMethodImpl(std::string strFuncName); 
		ICallableObject<Object> * GetCallableObject(Object obj);

	public:
		INT32   Dispatcher(ObjectMsgCall<Object> * pObjectMsgCall ,Object obj);

	public: 
		//5 注册静态类的函数 
		template<typename Object , typename Func>
		UINT32 RegisterFunc(const char * pFuncName , Func pFunc)
		{ 
			StaticMethodImpl<Object , Func> * pSMI = new StaticMethodImpl<Object , Func>;   //5 这里将函数封装在静态函数包里.
			pSMI->m_cMethodType = METHOD_TYPE_STATIC;  
			STRCPY_SAFE(pSMI->m_pMehtodName , MAX_MSG_METHOD_NAME_LENGTH , pFuncName ); 
			pSMI->m_objFunc = pFunc;
			pSMI->m_pMethodImpl = StaticMethodImplHelper::CallFuncEntry<Object , Func>;
			 
			MapMethodImplT::accessor result; 
			if (!m_mapMethodImpls.insert(result , pFuncName))
			{
				SAFE_DELETE(pSMI);
				return FALSE;
			}
			result->second = pSMI;
			return TRUE;
		}
		 
		//5 注册对象类的函数 , 这里使用了一个小技巧.只传递类对象.Func是可以从参数推到出来的. 
		template<typename Object , typename ClassObject , typename Func>
		UINT32 RegisterFunc(const char * pFuncName , Func pFunc)
		{ 
			ObjectMethodImpl<Object , ClassObject , Func> * pOMI = new ObjectMethodImpl<Object , ClassObject , Func>; 
			pOMI->m_cMethodType = METHOD_TYPE_OBJECT;
			memcpy(pOMI->m_pMehtodName , pFuncName , MAX_MSG_METHOD_NAME_LENGTH);

			pOMI->m_objFunc = pFunc;
			pOMI->m_pObj = NULL;
			pOMI->m_pMethodImpl = ObjectMethodImplHelper::CallFuncEntry<Object , ClassObject , Func>;

			MapMethodImplT::accessor result; 
			if (!m_mapMethodImpls.insert(result , pFuncName))
			{
				SAFE_DELETE(pOMI);
				return FALSE;
			}
			result->second = pOMI;
			return TRUE;
		}

	private:
		MapMethodImplT       m_mapMethodImpls;
		MapCallableObjectsT  m_mapCallableObjects;
	}; 

	template<typename Object>
	MsgDispatcher<Object>::~MsgDispatcher()
	{
 		m_mapCallableObjects.clear();

		//5 这里不清空.只是简单的删除.
		MapMethodImplT::iterator iterMethodImpl = m_mapMethodImpls.begin();
		for (;iterMethodImpl != m_mapMethodImpls.end();++iterMethodImpl)
		{
			SAFE_DELETE(iterMethodImpl->second);
		} 
	}

	template<typename Object>
	MethodImpl<Object> * MsgDispatcher<Object>::GetMethodImpl( std::string strFuncName )
	{
		MapMethodImplT::accessor result; 
		if (m_mapMethodImpls.find(result , strFuncName))
		{
			return result->second;
		}
		return NULL; 
	}

	template<typename Object>
	ICallableObject<Object> * MsgDispatcher<Object>::GetCallableObject( Object obj )
	{
		MapCallableObjectsT::accessor result;
		if (m_mapCallableObjects.find(result , obj))
		{  
			return result->second;
		}
		return NULL; 
	}

	template<typename Object>
	INT32 MsgDispatcher<Object>::DelCallableObject( ICallableObject<Object> * pCallableObject )
	{
		MapCallableObjectsT::accessor result;
		if (!m_mapCallableObjects.find(result , pCallableObject->GetObjectID()))
		{ 
			m_mapCallableObjects.erase(pCallableObject->GetObjectID());

			return TRUE;
		}
		return FALSE;
	}

	template<typename Object>
	INT32 MsgDispatcher<Object>::AddCallableObject( ICallableObject<Object> * pCallableObject )
	{
		MapCallableObjectsT::accessor result;
		if (!m_mapCallableObjects.find(result , pCallableObject->GetObjectID()))
		{
			m_mapCallableObjects.insert(std::make_pair(pCallableObject->GetObjectID() , pCallableObject));

			return TRUE;
		}
		return FALSE;
	}

	template<typename Object>
	INT32 MsgDispatcher<Object>::Dispatcher( ObjectMsgCall<Object> * pObjectMsgCall ,Object obj )
	{
		Assert_Re0(pMsgCall);
		ParaseMsgCall<Object> objParseMsgCall; 
		objParseMsgCall.m_pMsgCall = pObjectMsgCall;

		objParseMsgCall.m_pMehtodImpl = GetMethodImpl(objParseMsgCall.m_pMsgCall->m_szMsgMethod);  
		Assert_Re0(objParseMsgCall.m_pMehtodImpl); 
		 
		if (objParseMsgCall.m_pMehtodImpl->m_cMethodType == METHOD_TYPE_STATIC)
		{
			objParseMsgCall.m_pMehtodImpl->m_pMethodImpl(&objParseMsgCall);
		} 
		else
		{
			MapCallableObjectsT::accessor result;
			if (m_mapCallableObjects.find(result , pCallableObject->GetObjectID()))
			{
				objParseMsgCall.m_pObj = result->second; 
				objParseMsgCall.m_pMehtodImpl->m_pMethodImpl(&objParseMsgCall);
			} 
			else
				Assert_Re0(0);
		}

		return TRUE; 
	}
	 
}

#endif
