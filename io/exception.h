#ifndef IOException_h
#define IOException_h

#include <exception/exception.h>

namespace archendale
{

	class EOFException : public Exception
	{
	public:
		EOFException() : Exception() { ; }
		EOFException(string msg) : Exception(msg) { ; }
		EOFException(const EOFException& exp) : Exception(exp) { ; }
		virtual ~EOFException() { ; }	
	}; // EOFException

} // archendale

#endif // IOException_h
