#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <String/String.h>
#include <Exception/Exception.h>
namespace archendale 
{
	class ThreadParameterOutsideOfMemorySpaceException : Exception
	{
	}; // ThreadParameterOutsideOfMemorySpaceException
	
	class ThreadNotStartedException : Exception
	{
	}; // ThreadNotStartedException
	
	class ThreadNotFoundException : Exception
	{
	}; // ThreadNotFoundException

	class ThreadResourcesNotAvailableException : Exception
	{
	}; // ThreadResourcesNotAvailableException

	class ThreadDetachedException : Exception
	{
	}; // ThreadDetachedException

	class ThreadRequestSelfJoinException : Exception
	{
	}; // ThreadRequestSelfJoinException

	class InvalidThreadAttributeException : Exception
	{
	public:
		InvalidThreadAttributeException() {}; 
		InvalidThreadAttributeException(const String& msg) : Exception(msg) {};
		~InvalidThreadAttributeException() {};
	}; // InvalidThreadAttributeException

        class ThreadScheduleInsufficientPermission : Exception
        {
	public:
                ThreadScheduleInsufficientPermission() {};
                ThreadScheduleInsufficientPermission(const String& msg) : Exception(msg) {};
                ~ThreadScheduleInsufficientPermission() {};
        }; // InvalidThreadAttributeException

} // archendale
#endif // THREADEXCEPTION_H
