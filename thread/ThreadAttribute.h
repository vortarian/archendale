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

#ifndef THREADATTRIBUTE_H
#define THREADATTRIBUTE_H

#include <pthread.h>
#include <errno.h>
#include <exception/Exception.h>
#include <thread/ThreadException.h>

namespace archendale {

	class ThreadAttribute
	{
	public:
		ThreadAttribute();
		virtual ~ThreadAttribute();
		ThreadAttribute(const ThreadAttribute&);
	
		bool operator==(const ThreadAttribute&) const;
		bool operator==(const pthread_attr_t&) const;
		const ThreadAttribute& operator=(const ThreadAttribute&);
/**
 * Pthreads documentation indicates that the thread attribute should be considered opague, so not allowing direct copying here
 * @see man pthread_attribute_initialize
		const pthread_attr_t& operator=(const pthread_attr_t&);
 */
	
		const pthread_attr_t& getAttribute() const;
	
		//
		// Thread State
		//	DEFAULT: setCreateJoinable()
		//
	
		// setCreateJoinable:
		//	Create Thread so that it's resources are not freed until parent Thread calls join()
		void setCreateJoinable();
               
private: 
/* TODO
		Detached Threads are seg faulting because their object handle goes out of scope
                        before the thread destructor's call to pthread_cancel exits.
                        This happens because pthread_cancel does not block.
                        This could possibly be fixed by setting all detached
                        ThreadSuper's to use PTHREAD_CANCEL_ASYNCHRONOUS
                        The preferred method is to switch to a handle/body reference counted
                        implemententation so the Object is in Scope until actual cleanup can be performed
                        FOR NOW, setCreateDetached() IS BEING MADE PRIVATE, SO IT CAN NOT BE CALLED
*/
		// setCreateDetached:
		//	Create the Thread so that it's resources and execution are independent
		//	of Parent Thread
		void setCreateDetached();
	
public:		
		// getDetachState:
		//	returns true if state is set to PTHREAD_CREATE_DETACHED
		bool getDetachState() const;
	
		//
		// Scheduling Policies
		// DEFAULT: setScheduleRegular()
		// DEFAULT: setExplicitSchedule()
		// NOTE: Only Regular scheduling policies are available to processes not running as root
		//
	
		// setScheduleRegular:
		//	regular, non-realtime scheduling
		void setScheduleRegular();

		// isScheduleRegular:
		//	true if scheduling is regular, non-realtime scheduling
		bool isScheduleRegular() const;

		//
		// Realtime Issues
		//	
		
		// setScheduleRoundRobin:
		//	real-time, round robin scheduling
		//	Takes an optional attribute to set the priority
		void setScheduleRoundRobin(int = 1);
	
		// isScheduleRoundRobin:
		//	true if scheduling is real-time, round robin scheduling
		bool isScheduleRoundRobin() const;

		// setScheduleFifo:
		//	real-time, First-in First-out scheduling
		//	Takes an optional attribute to set the priority
		void setScheduleFifo(int = 1);
	
		// isScheduleFifo:
		//	true if scheduling is real-time, First-in First-out scheduling
		bool isScheduleFifo() const;

		// setSchedulePriority
		//	valid values: 0 - 99
		//	Sets the scheduling priority for the thread
		void setSchedulePriority(int);
		
		// getSchedulePriority
		//	returns the current scheduling priority
		int getSchedulePriority() const;
		
		// getScheduleParameter
		//	returns the scheduling parameter
		const sched_param& getScheduleParameter() const;
	
		// setExplicitSchedule:
		//	Set the scheduling policy from set attributes
		void setExplicitSchedule();
	
		// setInheritParentSchedule:
		//	Inherit the scheduling policy from the parent thread
		void setInheritParentSchedule();
	
		//
		// Scope 
		//	NOTE: LinuxThreads only supports system scope at time of writing
		//
	
		// setScopeSystem:
		void setScopeSystem();
	
		// setScopeProcess
		void setScopeProcess();
	
	private:
		pthread_attr_t m_threadAttribute;
		mutable sched_param m_scheduleParameter;	 		// The System schedule policy
	}; // ThreadAttribute
} // archendale
#endif // THREADATTRIBUTE_H
