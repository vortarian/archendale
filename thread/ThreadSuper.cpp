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

#include <thread/ThreadSuper.h>
#include <thread/AutoMutex.h>
#include <thread/AutoMutexTry.h>
#include <util/ReferenceCounter.h>
#include <unistd.h> // for sleep()

/*
        TODO:
                Need to add support for cancellation beyond just stop (see man pthread_cancel)
                Need to add support for test_cancel 
                Need to add support for pthread_rwlock
                Need to add supper for pthread_yield, or change wait to not use sleep()
                Need to add functionality to lookup the ThreadSuper object which is currently executing
                Detached Threads are seg faulting because their object handle goes out of scope
                        before the thread destructor's call to pthread_cancel exits.
                        This happens because pthread_cancel does not block.
                        This could possibly be fixed by setting all detached
                        ThreadSuper's to use PTHREAD_CANCEL_ASYNCHRONOUS - which is advised as non-useful in the pthread_setcancelstate man page
                        Current workaround would be to create the threaded object as a pointer, and keep it in scope
                        The preferred method is to switch to a handle/body reference counted
                        implemententation so the Object is in Scope until actual cleanup can be performed
                        FOR NOW, detach() IS BEING MADE PRIVATE, SO IT CAN NOT BE CALLED
 * 		Joinable threads are segfaulting the same way detached threads are seg faulting
 */

namespace archendale {

    ThreadSuper::ThreadSuper() {
        m_threadHandle = 0;
        m_running = false;
    } // ThreadSuper

    ThreadSuper::ThreadSuper(const ThreadAttribute& attr) {
        m_threadHandle = 0;
        m_threadAttribute = attr;
        m_running = false;
    } // ThreadSuper

    ThreadSuper::~ThreadSuper() {
        // TODO: All Joinable threads must be joined, if they are not, 
        //	then the destructor should take care of this
        try {
            stop();
        } catch (ThreadNotFoundException exp) {
            // No need to do anything the thread isn't running!
        } // try
    } // ~ThreadSuper

    void ThreadSuper::start(Thread* thread) {
        if (m_running == true) {
            ThreadRunningException exp;
            throw exp;
        } // if
        pthread_attr_t attr = m_threadAttribute.getAttribute();
        switch (pthread_create(&m_threadHandle, &attr, (void* (*)(void*)) & _run, thread)) {
            case EAGAIN:
            {
                ThreadResourcesNotAvailableException exp;
                throw exp;
            }
			break;
        } // switch
    } // start

    void ThreadSuper::stop() {
		// If it is not running, it is because the thread has already completed is operation (@see ThreadSuper->_run()) and it is unnecessary to stop it
		if(m_running == true) {
        // m_running must be updated before the cancel
        // otherwise if an exception gets thrown, we will
        // exit without telling the thread it is no longer
        // running!
			if(m_threadHandle == 0) 
				return;
			if (pthread_equal(pthread_self(), m_threadHandle)) {
				pthread_exit(0);
			} else {
				switch (pthread_cancel(m_threadHandle)) {
					case ESRCH:
						ThreadNotFoundException exp;
						throw exp;
						break;
				} // switch
			}
        // Setting m_running last due to the ability to deadlock during the join (caused by the locking of the mutex in join(), stop() and _run()
			AutoMutex aMutex(m_stateMutex);
			m_running = false;
			// Clear the thread handle
			m_threadHandle = 0;
        }
    } // stop

    void ThreadSuper::join() {
		if(m_threadHandle == 0)
			return;
        switch (pthread_join(m_threadHandle, 0)) {
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
        // Setting m_running last due to the ability to deadlock during the join (caused by the locking of the mutex in join(), stop() and _run()
        AutoMutex aMutex(m_stateMutex);
        m_running = false;
    } // join

    // detach:
    //      Detach the current thread while executing
    //      detach() will try to lock m_joinOrDetachMutex, if it fails
    //      it will throw ThreadJoinInProcessException

    void ThreadSuper::detach() {
        try {
            AutoMutexTry autoTryMutex(m_stateMutex);
            switch (pthread_detach(m_threadHandle)) {
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
        } catch (MutexBusyException mbeexp) {
            ThreadJoinInProgressException exp;
            exp.setNestedException(mbeexp);
            throw exp;
        } // try
    } // detach

    bool ThreadSuper::operator==(const ThreadSuper& rhs) const {
        return pthread_equal(getThread(), rhs.getThread());
    } // operator==

    // Note that running states, and thread handles will not
    // be copied, as it is not MT Safe

    const ThreadSuper& ThreadSuper::operator=(const ThreadSuper& rhs) {
        setAttribute(rhs.getAttribute());
		m_running = rhs.m_running;
		m_threadHandle = rhs.m_threadHandle;
        return *this;
    } // operator=

    const pthread_t& ThreadSuper::getThread() const {
        return m_threadHandle;
    } // getThread

    const ThreadAttribute& ThreadSuper::getAttribute() const {
        return m_threadAttribute;
    } // getAttribute

    // Remember, this is a static method!
    void* ThreadSuper::_run(Thread* _this) {
        // Why set m_running here instead of start?
        // For the odd, extremely rare, probably never 
        // happen possibility that the thread gets 
        // killed between the call of start and run!
        _this->m_thread->m_running = true;
        _this->run();
        // once _this->run() returns, we have stopped running
// TODO:  Uncommenting this, might have needed this to continue being set to false or possibly done in the destructor
        // Setting m_running last due to the ability to deadlock during the join (caused by the locking of the mutex in join(), stop() and _run()
        AutoMutex amut(_this->m_thread->m_stateMutex);
        _this->m_thread->m_running = false;
    } // _run

    void ThreadSuper::setAttribute(const ThreadAttribute& attr) {
        m_threadAttribute = attr;
    } // setAttribute

    // scheduleFifo:

    void ThreadSuper::scheduleFifo(int priority) {
        m_threadAttribute.setScheduleFifo(priority);
        if (!m_running) return;
        switch (pthread_setschedparam(m_threadHandle, SCHED_FIFO, &m_threadAttribute.getScheduleParameter())) {
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

    void ThreadSuper::scheduleRoundRobin(int priority) {
        m_threadAttribute.setScheduleRoundRobin(priority);
        if (!m_running) return;
        switch (pthread_setschedparam(m_threadHandle, SCHED_RR, &m_threadAttribute.getScheduleParameter())) {
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


    ///////////////////////////////////////////////////////////////
    //
    // 	Static Utility Methods, methods that can be called
    //	from any instance at any time
    //
    ///////////////////////////////////////////////////////////////

    // wait:

    void ThreadSuper::wait(unsigned int delay) {
        sleep(delay);
    } // wait

    //
    // The actual thread class

    Thread::Thread() : m_thread(new ThreadSuper()) {
    } // Thread

    Thread::Thread(const ThreadAttribute& attr) : m_thread(new ThreadSuper(attr)) {
    } // Thread

    Thread::~Thread() {
    } // ~Thread

    void Thread::start() {
        m_thread->start(this);
    } // start

    void Thread::stop() {
        m_thread->stop();
    } // stop

    void Thread::join() {
        m_thread->join();
    } // join

    // detach:
    //      Detach the current thread while executing
    //      detach() will try to lock m_joinOrDetachMutex, if it fails
    //      it will throw ThreadJoinInProcessException
    void Thread::detach() {
        m_thread->detach();
    } // detach

    bool Thread::operator==(const Thread& rhs) const {
		return *m_thread == *rhs.m_thread;
    } // operator==

    const Thread& Thread::operator=(const Thread& rhs) {
		*m_thread = *rhs.m_thread;
        return *this;
    } // operator=

    const pthread_t& Thread::getThread() const {
        return m_thread->getThread();
    } // getThread

    const ThreadAttribute& Thread::getAttribute() const {
        return m_thread->getAttribute();
    } // getAttribute

    void Thread::setAttribute(const ThreadAttribute& attr) {
        m_thread->setAttribute(attr);
    } // setAttribute

    // scheduleFifo:
    void Thread::scheduleFifo(int priority) {
	m_thread->scheduleFifo(priority);
    } // scheduleFifo

    // scheduleRoundRobin:
    void Thread::scheduleRoundRobin(int priority) {
	m_thread->scheduleRoundRobin(priority);
    } // scheduleRoundRobin

    ///////////////////////////////////////////////////////////////
    //
    // 	Static Utility Methods, methods that can be called
    //	from any instance at any time
    //
    ///////////////////////////////////////////////////////////////

    // wait:
    void Thread::wait(unsigned int delay) {
	ThreadSuper::wait(delay);
    } // wait

} // archendale
