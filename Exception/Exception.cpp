#include <iostream>
#include <Exception/Exception.h>

namespace archendale 
{
	Exception::Exception()
	{
		m_isNested = false;
		m_nestedException = 0;
	} // constructor
	
	Exception::Exception(const string& msg)
	{
		m_msg = msg;
		m_isNested = false;
		m_nestedException = 0;
	} // constructor
	
	Exception::~Exception()
	{
		if(m_isNested) 
		{
			delete m_nestedException;
		} // if
	} // destructor
	
	Exception::Exception(const Exception& exp)
	{
		m_msg = exp.why();
		if(exp.hasNested()) 
		{
			m_nestedException = new Exception();
			(*m_nestedException) = (exp.getNestedException());
			m_isNested = true;
		} else {
			m_nestedException = 0;
			m_isNested = false;
		} // if
	} // copy constructor

	const Exception& Exception::operator=(const Exception& exp)
	{
		m_msg = exp.why();
		if(exp.hasNested())
		{
			m_nestedException = new Exception(exp.getNestedException());
			m_isNested = true;
		} else {
			m_nestedException = 0;
			m_isNested = false;
		} // if
	} // operator =	

	string Exception::why() const
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
			std::cerr << "No Nested Exception being thrown" << std::endl;
			Exception exp("No Nested Exception");
			throw exp;
		} // if
		return *m_nestedException;
	} // getNestedException

	// setNestedException:
	//	Append an exception to this one, so as to ensure
	//	that exceptions are not lost
	void Exception::setNestedException(const Exception& exp)
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
	NotImplementedException::NotImplementedException(const string& msg) : Exception(msg)
	{
		std::cerr << "Unimplemented Function has been executed" << std::endl;
	} // NotImplementedException

	// ~NotImplementedException:
	// 	Exception throw when a method/object is not implemented
	NotImplementedException::~NotImplementedException()
	{
	} // ~NotImplementedException
} // archendale
