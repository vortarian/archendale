#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <String/String.h>

namespace archendale 
{
	class Exception 
	{
	public:
		Exception();
		Exception(const String&);
		virtual ~Exception();
		Exception(const Exception&);

		// operators
		const Exception& operator=(const Exception& exp);
	
		// why:
		//	Returns message that applies to the exception
		String why() const;
		
		// hasNested:
		//	Return true if there is a nested exception
		//	otherwise return false
		bool hasNested() const;

		// getNestedException:
		//	Return the nested exception, by copy
		Exception getNestedException() const;
		
		// setNestedException:
		//	Append an exception to this one, so as to ensure
		//	that exceptions are not lost
		void setNestedException(const Exception& exp); 
	private:
		String m_msg;			// message, if any
		bool m_isNested;		// true if has nested exception
		Exception* m_nestedException;	// pointer to nested exception
	}; // Exception

	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		NotImplementedException(const String&);
		~NotImplementedException();
	}; // NotImplementedException

	class InvalidArgumentException : public Exception
	{
	public:
		InvalidArgumentException() : Exception() { ; }
		InvalidArgumentException(const String& msg) : Exception(msg) { ; }
		~InvalidArgumentException() { ; }
	}; // InvalidArgumentException

	class OutOfMemoryException : public Exception
	{
	public:
		OutOfMemoryException() : Exception() { ; }
		OutOfMemoryException(const String& msg) : Exception(msg) { ; }
		~OutOfMemoryException() { ; }
	}; // OutOfMemoryException
} // archendale

#endif // EXCEPTION_H
