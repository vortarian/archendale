#ifndef ReferenceCounter_h
#define ReferenceCounter_h

#include <Exception/Exception.h>

namespace archendale
{
	template <class T> class _ref
	{
	public:
		// Constructor
		_ref() { 
			m_count = 0;
			m_data = 0;
			m_count = new unsigned int;
			m_data = new T; 
			if(m_count == 0 || m_data == 0) 
			{
				string errString;
				OutOfMemoryException exp("Not Enough Memory to build _ref : " __FILE__);
				throw exp;
			} // if
			(*m_count) = 0;
			(*m_count)++; 
		} // _ref

		// Constructor
		_ref(T rhs) { 
			m_count = 0;
			m_data = 0;
			m_count = new unsigned int;
			m_data = new T(rhs); 
			if(m_count == 0 || m_data == 0) 
			{
				string errString;
				OutOfMemoryException exp("Not Enough Memory to build _ref : " __FILE__);
				throw exp;
			} // if
			(*m_count) = 0;
			(*m_count)++; 
		} // _ref

		// Copy Constructor
		_ref(const _ref& rhs) { 
			m_count = 0;
			m_data = 0;
			m_count = rhs.m_count;
			(*m_count)++;
			m_data = rhs.m_data;
		} // _ref

		// Destructor
		~_ref() {
			(*m_count)--;
			if(*m_count == 0) {
				delete m_count;
				delete m_data;
				m_count = 0;
				m_data = 0;
			} // if
		} // ~_ref

		T& operator*() { 
			return *m_data; 
		} // operator*

		const _ref& operator=(const _ref& rhs) {
			(*m_count)--;
			if(*m_count == 0) {
				delete m_data;
				delete m_count;
				m_count = 0;
				m_data = 0;
			} // if
		
			m_count = rhs.m_count;
			(*m_count)++;
			m_data = rhs.m_data;
			return *this;
		} // _ref
		
	private:

		T* m_data;
		unsigned int* m_count;
	}; // _ref

	template <class T> class RefCount
	{
	public:
		RefCount() { 
			m_pointer = 0;
			m_pointer = new _ref<T>(); 
			if(m_pointer == 0) 
			{
				string errString;
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
		} // RefCount

		RefCount(const T& value) { 
			m_pointer = 0;
			m_pointer = new _ref<T>(value); 
			if(m_pointer == 0) 
			{
				string errString;
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
		} // RefCount

		RefCount(const RefCount& rhs) { 
			m_pointer = 0;
			m_pointer = new _ref<T>(); 
			if(m_pointer == 0) 
			{
				string errString;
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
			*m_pointer = *rhs.m_pointer; 
		} // RefCount

		~RefCount() { 
			delete m_pointer; 
		} // RefCount

		T& operator*() { 
			return *(*m_pointer); 
		} // operator*

		RefCount<T>& operator=(const RefCount<T>& rhs) { 
			*m_pointer = *rhs.m_pointer; 
		}
	private:
		_ref<T>* m_pointer;	
	}; // it

} // namespace archendale
#endif // ReferenceCounter_h
