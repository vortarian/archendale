
#include <thread/AutoMutexTry.h>

namespace archendale
{
	AutoMutexTry::AutoMutexTry(Mutex& mutex) : m_mutex(mutex)
	{
		m_acquired = false;
		retry();
	} // AutoMutexTry

	AutoMutexTry::~AutoMutexTry()
	{
		if(m_acquired)
			m_mutex.release();
	} // ~AutoMutexTry

	void AutoMutexTry::retry()
	{
		if(m_acquired) return;
		try 
		{
			m_mutex.tryAcquire();
		} catch (MutexBusyException exp)	
		{
			m_acquired = false;
			throw exp;
		}
		m_acquired = true;
	} // ~AutoMutexTry
} // archendale
