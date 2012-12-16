#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <string>
#include <exception/exception.h>

using std::string;

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
		InvalidThreadAttributeException(const string& msg) : Exception(msg) {};
		~InvalidThreadAttributeException() {};
	}; // InvalidThreadAttributeException

        class ThreadScheduleInsufficientPermission : public Exception
        {
	public:
                ThreadScheduleInsufficientPermission() {};
                ThreadScheduleInsufficientPermission(const string& msg) : Exception(msg) {};
                ~ThreadScheduleInsufficientPermission() {};
        }; // InvalidThreadAttributeException

        class MutexBusyException : public Exception
        {
                // Thrown when a mutex is acquired by another thread, and requesting
                //  thread has been denied
        };

        class MutexOwnedException : public Exception
        {
                // Thrown when a mutex is already locked by the requesting thread
        };

        class InvalidMutexAttributeException : public Exception
        {
                // Thrown when a mutex is attempted to be acquired with an invalid attribute
        };

        class MutexNotInitializedException : public Exception
        {
        };

        class MutexNotOwnedException : public Exception
        {
                // Thrown when a mutex is attempted to be released when the releasing
                //      does not currently own the mutex
        };

        class MutexLockedException : public Exception
        {
                // Thrown when a mutex is attempted to be destroyed, but is locked
        };

} // archendale
#endif // THREADEXCEPTION_H
