
#include <ThreadObject/AutoMutex.h>

namespace archendale
{

	AutoMutex::AutoMutex(Mutex& mutex) : m_mutex(mutex)
	{
		m_mutex.acquire();
	} // AutoMutex
	
	AutoMutex::~AutoMutex()
	{
		cerr << "~AutoMutex()" << endl;
		m_mutex.release();
		cerr << "Leaving ~AutoMutex()" << endl;
	} // ~AutoMutex

} // archendale
