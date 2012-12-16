#ifndef ReferenceCounter_h
#define ReferenceCounter_h

#include <exception/exception.h>

/**
 TODO: This class is not thread safe.  The _ref class needs to guarantee atomic operations concerning
 the accounting of its member data.
 */
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
				OutOfMemoryException exp("Not Enough Memory to build _ref : " __FILE__);
				throw exp;
			} // if
			(*m_count) = 0;
			(*m_count)++; 
		} // _ref

		/**
		 *  @param rhs Pointer to the ref counted data, ownership is consumed
		 */
		_ref(T *rhs) { 
			m_count = 0;
			m_data = 0;
			m_count = new unsigned int;
			m_data = rhs; 
			if(m_count == 0 || m_data == 0) 
			{
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

		T* operator->() { 
			return m_data; 
		} // operator->

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

	template <class T> class ReferenceCounter 
	{
	public:
		ReferenceCounter() { 
			m_pointer = 0;
			m_pointer = new _ref<T>(); 
			if(m_pointer == 0) 
			{
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
		} //ReferenceCounter 

		/**
 	 	 *  Takes ownership of the the value of T and tracks references to it
 	 	 */
		ReferenceCounter(T* value) { 
			m_pointer = 0;
			m_pointer = new _ref<T>(value); 
			if(m_pointer == 0) 
			{
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
		} //ReferenceCounter 

		/**
 	 	 *  Copies the value of T into the reference variable
 	 	 */
		ReferenceCounter(const T& value) { 
			m_pointer = 0;
			m_pointer = new _ref<T>(value); 
			if(m_pointer == 0) 
			{
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
		} //ReferenceCounter 

		ReferenceCounter(const ReferenceCounter& rhs) { 
			m_pointer = 0;
			m_pointer = new _ref<T>(); 
			if(m_pointer == 0) 
			{
				OutOfMemoryException exp("Not Enough Memory to build m_pointer: " __FILE__);
				throw exp;
			} // if
			*m_pointer = *rhs.m_pointer; 
		} //ReferenceCounter 

		~ReferenceCounter() { 
			delete m_pointer; 
		} //ReferenceCounter 

		T& operator*() { 
			return *(*m_pointer); 
		} // operator*

		const T& operator*() const { 
			return *(*m_pointer); 
		} // operator*

		T* operator->() { 
			return m_pointer->operator->(); 
		} // operator->

		const T* operator->() const { 
			return m_pointer->operator->(); 
		} // operator->

		ReferenceCounter<T>& operator=(const ReferenceCounter<T>& rhs) { 
			*m_pointer = *rhs.m_pointer; 
		}

		ReferenceCounter<T>& operator==(const ReferenceCounter<T>& rhs) const { 
			*m_pointer == *rhs.m_pointer; 
		}
	private:
		_ref<T>* m_pointer;	
	}; // it

} // namespace archendale
#endif // ReferenceCounter_h
