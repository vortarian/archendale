
#ifndef FactoryException_h
#define FactoryException_h

#include <exception/exception.h>

namespace archendale
{
	class ClassNotFoundException : public Exception
	{
	public:
		ClassNotFoundException() { ; }
		ClassNotFoundException(const string& msg) : Exception(msg) { ; }
	}; // ClassNotFoundException

	class FunctionNotFoundException : public Exception
	{
	public:
		FunctionNotFoundException() { ; }
		FunctionNotFoundException(const string& msg) : Exception(msg) { ; }
	}; // FunctionNotFoundException
} // archendale

#endif // FactoryException_h
