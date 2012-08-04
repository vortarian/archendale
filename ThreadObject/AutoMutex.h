#ifndef AUTOMUTEX_H
#define AUTOMUTEX_H

#include <ThreadObject/Mutex.h>

namespace archendale {

    // AutoMutex
    //	This class does block!  This ensures the locking
    //	of a mutex, without the developer having to worry about release
    //	Mutex is released when the object goes out of scope

    class AutoMutex {
    public:
        AutoMutex(Mutex& mutex);
        ~AutoMutex();
    private:

        const AutoMutex& operator=(const AutoMutex&) {
        };

        AutoMutex(const AutoMutex& autoMutex) : m_mutex(autoMutex.m_mutex) {
        };

        Mutex& m_mutex;
    }; // AutoMutex

} // archendale

#endif // AUTOMUTEX_H
