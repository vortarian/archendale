#include <iostream>

using namespace std;

template <class T> class _ref
{
public:
	_ref() { 
		m_count = 0;
		m_T = new T; 
		m_count++; 
	} // _ref

	_ref(T rhs) { 
		m_count = 0;
		m_T = new T; 
		*m_T = rhs;
		m_count++; 
	} // _ref

	~_ref() {
		m_count--;
		if(m_count == 0) {
			delete m_T;
		} // if
	} // ~_ref

	T& operator*() { 
		return *m_T; 
	} // operator*

	const _ref& operator=(const _ref& rhs) {
		m_count++;
		m_T = rhs.m_T;
		return *this;
	} // _ref
private:
	_ref(const _ref&) { 
		// don't want copy constructor used
	} // _ref


	T* m_T;
	int m_count;
}; // _ref

template <class T> class RefCount
{
public:
	RefCount() { 
		m_pointer = new _ref<T>(); 
	} // RefCount

	RefCount(const T& rhs) { 
		m_pointer = new _ref<T>(rhs); 
	} // RefCount

	RefCount(const RefCount& rhs) { 
		*m_pointer = *rhs.m_pointer; 
	} // RefCount

	~RefCount() { 
		delete m_pointer; 
	} // RefCount

	T& operator*() { 
		return *(*m_pointer); 
	} // operator*

	RefCount<T>& operator=(const RefCount<T>& rhs) { 
		m_pointer = rhs.m_pointer; 
	}
private:
	_ref<T>* m_pointer;	
}; // it
