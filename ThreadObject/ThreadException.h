#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <String/String.h>
#include <Exception/Exception.h>

namespace archendale 
{
	class ThreadJoinInProgressException : public Exception
	{
	}; // ThreadJoinInProgressException 
	
	class ThreadParameterOutsideOfMemorySpaceException : public Exception
	{
	}; // ThreadParameterOutsideOfMemorySpaceException
	
	class ThreadNotStartedException : public Exception
	{
	}; // ThreadNotStartedException
	
	class ThreadRunningException : public Exception
	{
		// Occurs when the thread is started while it is running!
	}; // ThreadRunningException
	
	class ThreadNotFoundException : public Exception
	{
	}; // ThreadNotFoundException

	class ThreadResourcesNotAvailableException : public Exception
	{
	}; // ThreadResourcesNotAvailableException

	class ThreadDetachedException : public Exception
	{
	}; // ThreadDetachedException

	class ThreadRequestSelfJoinException : public Exception
	{
	}; // ThreadRequestSelfJoinException

	class InvalidThreadAttributeException : public Exception
	{
	public:
		InvalidThreadAttributeException() {}; 
		InvalidThreadAttributeException(const String& msg) : Exception(msg) {};
		~InvalidThreadAttributeException() {};
	}; // InvalidThreadAttributeException

        class ThreadScheduleInsufficientPermission : public Exception
        {
	public:
                ThreadScheduleInsufficientPermission() {};
                ThreadScheduleInsufficientPermission(const String& msg) : Exception(msg) {};
                ~ThreadScheduleInsufficientPermission() {};
        }; // InvalidThreadAttributeException

} // archendale
#endif // THREADEXCEPTION_H
