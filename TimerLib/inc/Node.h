#ifndef __timer_node_h__
#define __timer_node_h__
#include "TimerCommon.h"
#include "ThreadLock.h"
#include "ClassTypeInterface.h" 

namespace Timer
{ 
	template<typename ValueType>
	class DLL_EXPORT Node : public Util::ClassTypeInterface
	{
		CLASS_TYPE_ID(Node<ValueType> , Util::ClassTypeInterface , CTID_Node)
	public:
		Node();
		explicit Node(ValueType objValue);
		virtual ~Node(void);

	public:
		void        SetNodePos(UINT32 unNodePos);
		INT32       GetNodePos( void );
		ValueType   GetValue( void );

	protected:
		ThreadPool::ThreadSpinRWMutex   m_objLock;

	private:
		INT32                m_unNodePos;
		ValueType            m_objValue;
	};

	template<typename ValueType>
	Node<ValueType>::Node()
		: m_unNodePos(-1)
		, m_objValue(0)
	{

	}

	template<typename ValueType>
	Node<ValueType>::Node( ValueType objValue )
		: m_unNodePos(-1)
		, m_objValue(objValue)
	{

	}

	template<typename ValueType>
	Node<ValueType>::~Node( void )
	{

	}

	template<typename ValueType>
	void Node<ValueType>::SetNodePos( UINT32 unNodePos )
	{
		ThreadPool::AutoSpinRWLock objLock(m_objLock); 
		m_unNodePos = unNodePos;  
	}

	template<typename ValueType>
	INT32 Node<ValueType>::GetNodePos( void )
	{
		ThreadPool::AutoSpinRWLock objLock(m_objLock , false); 
		return m_unNodePos; 
	}

	template<typename ValueType>
	ValueType Node<ValueType>::GetValue( void )
	{
		ThreadPool::AutoSpinRWLock objLock(m_objLock , false); 
		return m_objValue;
	} 
} 
 
 
#endif