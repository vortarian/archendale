//	Anyone may use this source, as long as they keep my name on it (author name), and 
//		do not modify the FILE STAMP below, give me credit if they borrow code, 
//		and send me an email saying that they plan to use it.  Nothing detailed, just something like:
//
//		Subject: Using your ThreadObjects
//		Contents should include: 
//			1) Type of project (Enterprise Finacial App, College Project, Corporate, making fun of you . . . :) 
//			2) Your opinion (opinion can be withheld to a later date if you have not had sufficient time to formulate)
//			3) Suggestions
//			4) Feel free to rag me on style, programming choices, etc, but please only do so if you are not providing a better suggestion :)
//
//  ***** BEGIN FILE STAMP *****
//  Author: Glenn Meuth
//  vortex@archendale.com
//  http://www.archendale.com/~vortex
//  Creation Date: May 28, 2000
//  ***** END FILE STAMP *****
//
//  Last Modified by: Glenn Meuth
//  Last Modified Date: May 28, 2000
//
//

#include <ThreadObject/ThreadSuper.h>
#include <ThreadObject/AutoMutex.h>
#include <ThreadObject/AutoMutexTry.h>

/*
	TODO:
		Need to add support for cancellation beyond just stop (see man pthread_cancel)
		Need to add support for test_cancel 
*/

namespace archendale 
{

	ThreadSuper::ThreadSuper()
	{
		m_running = false;
	} // ThreadSuper

	ThreadSuper::ThreadSuper(const ThreadAttribute& attr)
	{
		m_threadAttribute = attr;
		m_running = false;
	} // ThreadSuper

	ThreadSuper::~ThreadSuper()
	{
		try 
		{
			m_running = false;
			stop();
		} catch (ThreadNotFoundException exp) 
		{
			// No need to do anything the thread isn't running!
		} // try
	} // ~ThreadSuper

	void ThreadSuper::start()
	{
		if(m_running == true) {
			ThreadRunningException exp;
			throw exp;
		} // if
		pthread_attr_t attr = m_threadAttribute.getAttribute();
		switch(pthread_create(&m_threadHandle, &attr, &_run, this))
		{
			case EAGAIN:
				{
					ThreadResourcesNotAvailableException exp;
					throw exp;
				}
				break;
		} // switch
	} // start

	void ThreadSuper::stop()
	{
		// m_running must be updated before the cancel
		// otherwise if an exception gets thrown, we will
		// exit without telling the thread it is no longer
		// running!
		m_running = false;
		if(pthread_equal(pthread_self(), m_threadHandle))
		{
			cerr << endl << "Calling pthread_exit" << endl;
			pthread_exit(0);
		} else {
			cerr << endl << "Calling pthread_cancel" << endl;
			switch(pthread_cancel(m_threadHandle))
			{
				case ESRCH:
					ThreadNotFoundException exp;
					throw exp;
					break;
			} // switch
		}
	} // stop

	void ThreadSuper::join()
	{
		AutoMutex aMutex(m_joinOrDetachMutex);
		switch(pthread_join(m_threadHandle, 0))
		{
			case ESRCH:
				{
					ThreadNotFoundException tnfexp;
					throw tnfexp;
				}
				break;
			case EINVAL:
				{
					ThreadDetachedException tdexp;
					throw tdexp;
				}
				break;
			case EDEADLK:
				{
					ThreadRequestSelfJoinException exp;
					throw exp;
				}
				break;
		} // switch
		m_running = false;
	} // join

	// detach:
	//      Detach the current thread while executing
	//      detach() will try to lock m_joinOrDetachMutex, if it fails
	//      it will throw ThreadJoinInProcessException
	void ThreadSuper::detach()
	{
		try 
		{
			AutoMutexTry autoTryMutex(m_joinOrDetachMutex);
			switch(pthread_detach(m_threadHandle))
			{
				case ESRCH:
					{
						ThreadNotFoundException tnfexp;
						throw tnfexp;
					}
					break;
				case EINVAL:
					{
						ThreadDetachedException tdexp;
						throw tdexp;
					}
					break;
			} // switch
		} catch (MutexBusyException mbeexp) 
		{
			ThreadJoinInProgressException exp;
			exp.setNestedException(mbeexp);
			throw exp;
		} // try
	} // detach

	bool ThreadSuper::operator==(const ThreadSuper& rhs) const
	{
		return pthread_equal(getThread(), rhs.getThread());
	} // operator==

	// Note that running states, and thread handles will not
	// be copied, as it is not MT Safe
	const ThreadSuper& ThreadSuper::operator=(const ThreadSuper& rhs)
	{
		setAttribute(rhs.getAttribute());
		return *this;
	} // operator=

	const pthread_t& ThreadSuper::getThread() const
	{
		return m_threadHandle;
	} // getThread

	const ThreadAttribute& ThreadSuper::getAttribute() const
	{
		return m_threadAttribute;
	} // getAttribute

	// Remember, this is a static method!
	void* ThreadSuper::_run(ThreadSuper* _this) 
	{
		// Why set m_running here instead of start?
		// For the odd, extremely rare, probably never 
		// happen possibility that the thread gets 
		// killed between the call of start and run!
		_this->m_running = true;
		_this->run();	
		// one _this->run() returns, we have stopped running
		_this->m_running = false;
	} // _run

	void ThreadSuper::setAttribute(const ThreadAttribute& attr)
	{
		m_threadAttribute = attr;
	} // setAttribute

	// scheduleFifo:
	void ThreadSuper::scheduleFifo(int priority = 1)
	{
		m_threadAttribute.setScheduleFifo(priority);
		if(!m_running) return;
		switch(pthread_setschedparam(m_threadHandle, SCHED_FIFO, &m_threadAttribute.getScheduleParameter()))
		{
			case EINVAL:
				{
					InvalidThreadAttributeException exp;
					throw exp;
				}
				break;
			case EPERM:
				{
					ThreadScheduleInsufficientPermission exp("Must have root access to use this schedule priority");
					throw exp;
				}
				break;
			case ESRCH:
				{
					ThreadNotFoundException exp;
					throw exp;
				}
				break;
			case EFAULT:
				{
					ThreadParameterOutsideOfMemorySpaceException exp;
					throw exp;
				}
				break;
		} // switch
	} // scheduleFifo
	
	// scheduleRoundRobin:
	void ThreadSuper::scheduleRoundRobin(int priority = 1)
	{
		m_threadAttribute.setScheduleRoundRobin(priority);
		if(!m_running) return;
		switch(pthread_setschedparam(m_threadHandle, SCHED_RR, &m_threadAttribute.getScheduleParameter()))
		{
			case EINVAL:
				{
					InvalidThreadAttributeException exp;
					throw exp;
				}
				break;
			case EPERM:
				{
					ThreadScheduleInsufficientPermission exp("Must have root access to use this schedule priority");
					throw exp;
				}
				break;
			case ESRCH:
				{
					ThreadNotFoundException exp;
					throw exp;
				}
				break;
			case EFAULT:
				{
					ThreadParameterOutsideOfMemorySpaceException exp;
					throw exp;
				}
				break;
		} // switch
	} // scheduleRoundRobin

} // archendale
