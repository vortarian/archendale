#ifndef AUTOMUTEXTRY_H
#define AUTOMUTEXTRY_H

#include <ThreadObject/Mutex.h>

namespace archendale
{

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

#endif // AUTOMUTEXTRY_H
