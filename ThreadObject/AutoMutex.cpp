
#include <ThreadObject/AutoMutex.h>

namespace archendale
{

	AutoMutex::AutoMutex(Mutex& mutex) : m_mutex(mutex)
	{
		m_mutex.acquire();
	} // AutoMutex
	
	AutoMutex::~AutoMutex()
	{
		m_mutex.release();
	} // ~AutoMutex

} // archendale
