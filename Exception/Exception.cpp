
#include <Exception/Exception.h>

namespace archendale 
{

	Exception::Exception()
	{
		m_isNested = false;
		m_nestedException = 0;
	} // constructor
	
	Exception::Exception(const String& msg)
	{
		m_msg = msg;
		m_isNested = false;
		m_nestedException = 0;
	} // constructor
	
	Exception::~Exception()
	{
		if(hasNested()) 
		{
			delete m_nestedException;
		} // if
	} // destructor
	
	Exception::Exception(const Exception& exp)
	{
		m_msg = exp.why();
		if(exp.hasNested()) 
		{
			m_nestedException = new Exception(exp.getNestedException());
		} // if
	} // copy constructor
	
	String Exception::why() const
	{
		return m_msg;
	}  // why
	
	// hasNested:
	//	Return true if there is a nested exception
	//	otherwise return false
	bool Exception::hasNested() const
	{
		return m_isNested;
	} // hasNested
	
	// getNestedException:
	//	Return the nested exception, by copy
	Exception Exception::getNestedException() const 
	{
		if(!hasNested()) 
		{
			Exception exp("No Nested Exception");
			throw exp;
		} // if
		return *m_nestedException;
	} // getNestedException

	// setNestedException:
	//	Append an exception to this one, so as to ensure
	//	that exceptions are not lost
	void Exception::setNestedException(Exception exp)
	{
		m_nestedException = new Exception(exp);
		m_isNested = true;
	}
	
	// NotImplementedException:
	// 	Exception throw when a method/object is not implemented
	NotImplementedException::NotImplementedException()
	{
	} // NotImplementedException

	// NotImplementedException:
	// 	Exception throw when a method/object is not implemented
	NotImplementedException::NotImplementedException(const String& msg) : Exception(msg)
	{
		cerr << "Unimplemented Function has been executed" << endl;
	} // NotImplementedException

	// ~NotImplementedException:
	// 	Exception throw when a method/object is not implemented
	NotImplementedException::~NotImplementedException()
	{
	} // ~NotImplementedException
} // archendale
