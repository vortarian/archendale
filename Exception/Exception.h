#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

namespace archendale 
{
	class Exception 
	{
	public:
		Exception();
		Exception(const string&);
		virtual ~Exception();
		Exception(const Exception&);

		// operators
		const Exception& operator=(const Exception& exp);
	
		// why:
		//	Returns message that applies to the exception
		string why() const;
		
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
		string m_msg;			// message, if any
		bool m_isNested;		// true if has nested exception
		Exception* m_nestedException;	// pointer to nested exception
	}; // Exception

	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException();
		NotImplementedException(const string&);
		~NotImplementedException();
	}; // NotImplementedException

	class InvalidArgumentException : public Exception
	{
	public:
		InvalidArgumentException() : Exception() { ; }
		InvalidArgumentException(const string& msg) : Exception(msg) { ; }
		~InvalidArgumentException() { ; }
	}; // InvalidArgumentException

	class InvalidDataException : public Exception
	{
	public:
		InvalidDataException() : Exception() { ; }
		InvalidDataException(const string& msg) : Exception(msg) { ; }
		~InvalidDataException() { ; }
	}; // InvalidDataException

	class OutOfMemoryException : public Exception
	{
	public:
		OutOfMemoryException() : Exception() { ; }
		OutOfMemoryException(const string& msg) : Exception(msg) { ; }
		~OutOfMemoryException() { ; }
	}; // OutOfMemoryException

	class NotSupportedException : public Exception
	{
	public:
		NotSupportedException() : Exception() { ; }
		NotSupportedException(const string& msg) : Exception(msg) { ; }
		~NotSupportedException() { ; }
	}; // NotSupportedException

	class AccessDeniedException : public Exception
	{
	public:
		AccessDeniedException() : Exception() { ; }
		AccessDeniedException(const string& msg) : Exception(msg) { ; }
		~AccessDeniedException() { ; }
	}; // AccessDeniedException


	class ObjectNotFoundException : public Exception
	{
	public:
		ObjectNotFoundException () : Exception() { ; }
		ObjectNotFoundException (const string& msg) : Exception(msg) { ; }
		~ObjectNotFoundException () { ; }
	}; // ObjectNotFoundException 

} // archendale

#endif // EXCEPTION_H
