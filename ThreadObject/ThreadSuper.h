#ifndef THREADSUPER_H
#define THREADSUPER_H
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
//  Last Modified Date: May 28, 2000
//
//
 
#include <pthread.h>
#include <errno.h>
#include <ThreadObject/ThreadAttribute.h>
#include <ThreadObject/ThreadException.h>

namespace archendale 
{

	// ThreadSuper:
	//
	//	Super class object that all class which will begin a thread of execution should inherit from.
	//	A client should inherit from this class, and define the pure virtual method run, which will 
	//	be executed as the thread
	//	
	class ThreadSuper {
	public:
		ThreadSuper();
		ThreadSuper(const ThreadAttribute& attr);
		virtual ~ThreadSuper();
	
		// start:
		//	Begin execution of thread
		void start();

		// Stop:
		// Stop execution of thread as quickly as possible
		void stop();
	
		// Join:
		// Join the thread to the main thread, wait if necessary
		void join();

		// compares thread id's to see if they equal
		bool operator==(const ThreadSuper&) const;
		// deep copy of the incoming object,
		// this may be dangerous, as two thread handles
		// floating around . . . .
		const ThreadSuper& operator=(const ThreadSuper&);	
	
		// getThread:
		// Get the Thread handle
		const pthread_t& getThread() const;
	
		// getAttribute:
		// Get a copy of the current Attribute Object for this thread 
		const ThreadAttribute& getAttribute() const;
	
		// setAttribute:
		// Set the current attribute for this thread
		void setAttribute(const ThreadAttribute&);
		
		///////////////////////////////////////////////////////////////
		//
		//	Schedule Altering
		//		Can be used to change the scheduling while
		//		the process is executing
		//
		///////////////////////////////////////////////////////////////
		
		// scheduleFifo:
		//	Changes the scheduling type to Fifo
		//	Takes an optional parameter to set priority
		//	Note: Only processes running as root can do this
		void scheduleFifo(int = 1);
		
		
		// scheduleRoundRobin:
		//	Changes the scheduling type to RoundRobin
		//	Takes an optional parameter to set priority
		//	Note: Only processes running as root can do this
		void scheduleRoundRobin(int = 1);
	private:	
		// run:
		//	function that is defined by the subclass to
		//	execute what the thread actually does
		virtual void run() = 0;

		// Start routine for the thread, it is a kickoff routine not to be called
		// by any function except ThreadSuper::start
		static void* _run(ThreadSuper*);

		bool m_running;
		pthread_t m_threadHandle;
		ThreadAttribute m_threadAttribute;
	};
} // archendale

#endif // THREADSUPER_H
