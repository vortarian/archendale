//	Anyone may use this source, as long as they keep my name on it (author name), and 
//		do not modify the FILE STAMP below, give me credit if they borrow code, 
//		and send me an email saying that they plan to use it.  Nothing detailed, just something like:
//
//		Subject: Using your ThreadObjects
//		Contents should include: 
//			1) Type of project (Enterprise Finacial App, Colledge Project, Corporate . . .)
//			2) Your opinion (opinion can be withheld to a later date if you have not had sufficient time to formulate)
//			3) Suggestions
//			4) Feel free to rag me on style etc, but please only do so if you are not providing a better suggestion :)
//
//  ***** BEGIN FILE STAMP *****
//  Author: Glenn Meuth
//			vortex@archendale.com
//			http://www.archendale.com/~vortex
//  Creation Date: May 28, 2000
//  ***** END FILE STAMP *****
//
//  Last Modified by: Glenn Meuth
//  Last Modified Date: May 29, 2000
//
//

#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include <errno.h>
#include <thread/MutexException.h>

namespace archendale 
{
	class Mutex
	{
	public:
		Mutex();
		virtual ~Mutex();

		// acquire:
		// 	Get the mutex for use
		//	NOTE: This function call blocks
		virtual void acquire();

		// tryAcquire:
		// 	Get the mutex for use
		//	NOTE: This function call does not block
		//	Throws MutexBusyException if lock has not been acquired
		bool tryAcquire();

		// release:
		//	Let go of the mutex
		void release();

	private:
		Mutex(const Mutex&) {} // Should not be created via copy constructor
		bool operator=(const Mutex&) {} // Mutex's should not be assigned
		bool operator==(const Mutex&) {} // Mutex's should not be compared
		pthread_mutex_t m_mutex;
		pthread_mutexattr_t m_mutexAttribute;
	}; // Mutex

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

	// AutoMutexTry
	//	This class does not block!  This ensures the locking
	//	of a mutex, or the throwing of the exception MutexBusyException,
	//	without the developer having to worry about release
	//	Mutex is released when the object goes out of scope
	class AutoMutexTry
	{
	public:
		AutoMutexTry(Mutex&);
		~AutoMutexTry();

		// retry:
		// 	Used to attempt to retry the mutex acquire
		void retry();
	private:
		const AutoMutexTry& operator=(const AutoMutexTry&) {};
		AutoMutexTry(const AutoMutexTry& mutex) : m_mutex(mutex.m_mutex) {};
		// set to true if acquired, otherwise false
		bool m_acquired;
		Mutex& m_mutex;	
	}; // AutoMutexTry

} // archendale
#endif // THREADMUTEX_H
