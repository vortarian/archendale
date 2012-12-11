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

#include <thread/Mutex.h>

namespace archendale 
{

	Mutex::Mutex() 
	{
		pthread_mutexattr_init(&m_mutexAttribute);
		pthread_mutex_init(&m_mutex, &m_mutexAttribute);
	} // Mutex

	Mutex::~Mutex() 
	{
		pthread_mutexattr_destroy(&m_mutexAttribute);
		if(EBUSY == pthread_mutex_destroy(&m_mutex))
		{
			MutexLockedException exp;
			throw exp;
		}
	}

	// acquire:
	// 	Get the mutex for use
	//	NOTE: This function call blocks
	void Mutex::acquire()
	{
		switch(pthread_mutex_lock(&m_mutex)) 
		{
			case EINVAL:
				{
					MutexNotInitializedException mniexp;
					throw mniexp;
				}
				break;
			case EDEADLK:
				{
					MutexOwnedException moexp;
					throw moexp;
				}
				break;
		} // switch
	}

	// tryAcquire:
	// 	Get the mutex for use
	//	NOTE: This function call does not block
	//	Throws MutexBusyException if lock has not been acquired
	bool Mutex::tryAcquire()
	{
		switch(pthread_mutex_trylock(&m_mutex))
		{
			case EBUSY:
				{
					MutexBusyException mbexp;
					throw mbexp;
				}
				break;
			
			case EINVAL:
				{
					MutexNotInitializedException mniexp;
					throw mniexp;
				}
				break;
		} // switch
	}

	// release:
	//	Let go of the mutex
	void Mutex::release()
	{
		switch(pthread_mutex_unlock(&m_mutex))
		{
			case EPERM:
				{
					MutexNotOwnedException mnoexp;
					throw mnoexp;
				}
				break;
			case EINVAL:
				{
					MutexNotInitializedException mniexp;
					throw mniexp;
				}
				break;
		} // switch
	}
} // archendale
