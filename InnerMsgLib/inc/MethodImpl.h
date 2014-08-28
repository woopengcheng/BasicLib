#ifndef __msg_method_impl_h__
#define __msg_method_impl_h__
#include "ObjectMsgCall.h"

namespace Msg 
{  
	template<typename Object> class ParaseMsgCall;

	enum EMethodType
	{
		METHOD_TYPE_ERROR = 0,
		METHOD_TYPE_STATIC ,    //5 ��̬������������
		METHOD_TYPE_OBJECT ,    //5 ������������
	};
	  
	//5 ������Ҫ�Ժ������з�װ.��Ϊÿ����Ϣ�ľ��庯������ͨ��ͳһ�ĺ���ģ��ķ�ʽʵ��.
	template<typename Object> 
	class MethodImpl
	{ 
	public:
		typedef void (*pfnMethodImpl)(ParaseMsgCall<Object> * pParseMsgCall);

	public:
		 UINT8          m_cMethodType;      //5 �������Ϣ����������
		 char           m_pMehtodName[MAX_MSG_METHOD_NAME_LENGTH]; //5 ������������
		 pfnMethodImpl  m_pMethodImpl;      //5 ����Ϣ������һ����װ. 
	};
	 

	template<typename Object , typename Func>
	class StaticMethodImpl : public MethodImpl<Object>
	{
	public:
		Func m_objFunc;    //5 �������ģ��ķ�ʽ������ÿ����Ϣ�ĺ���.
	};

	template<typename Object , typename ClassObject , typename Func>
	class ObjectMethodImpl : public MethodImpl<Object>
	{
	public:
		ClassObject * m_pObj;       //5 ������Ϣ�ľ������.
		Func          m_objFunc;    //5 �������ģ��ķ�ʽ������ÿ����Ϣ�ĺ���.
	};
}

#endif
