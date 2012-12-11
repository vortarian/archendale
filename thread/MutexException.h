
#ifndef MUTEXEXCEPTION_H
#define MUTEXEXCEPTION_H

#include <exception/Exception.h>

namespace archendale
{

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

#endif // MUTEXEXCEPTION_H
