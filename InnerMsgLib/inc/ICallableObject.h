#ifndef __msg_i_msg_object_h__
#define __msg_i_msg_object_h__ 
#include "MsgCommon.h" 

namespace Msg
{  
	template<typename Object>
	class ICallableObject
	{
	public:
		ICallableObject(Object obj):m_objID(obj){}
		virtual ~ICallableObject(){}
	
	public:
		//************************************
		// Method:    Update
		// FullName:  Msg::ICallableObject<Object>::Update
		// Access:    virtual public 
		// Returns:   INT32
		// Qualifier: Update����Ϊ���󹩸���������õ�ʱ��ʹ��.
		//************************************
		virtual INT32 Update(){ return 0; } 

	public:
		virtual Object  GetObjectID(){ return m_objID; }                   //5 �������Ҳ��������.����û�������Ҫ.
		virtual void    SetObjectID(Object objID){ m_objID = objID; }
	
	private:
		Object      m_objID;
	};
	
	class IMsgCallableObject : public ICallableObject<MSG_ID>
	{
		public:
			IMsgCallableObject(MSG_ID id):ICallableObject<MSG_ID>(id){}
	};
}
#endif