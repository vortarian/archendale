//	Anyone may use this source, as long as they keep my name on it (author name), and 
//		do not modify the FILE STAMP below, give me credit if they borrow code, 
//		and send me an email saying that they plan to use it.  Nothing detailed, just something like:
//
//		Subject: Using your ThreadObjects
//		Contents should include: 
//			1) Type of project (Enterprise Finacial App, College Project, Corporate . . .)
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

#include <thread/attribute.h>

namespace archendale 
{
	////////////////////////////////////////////////////////////////////////////////////////
	// Constructors / Destructor
	////////////////////////////////////////////////////////////////////////////////////////

	// ThreadAttribute:
	//	ThreadAttribute is meant to be the encapsulation of the possible attributes for 
	//	a given threading library. This should probably be a super class with the worker 
	//	class being more platform specific, but I will leave that for a time when I get
	//	better understanding of what this class means to different threading libraries.
	//
	//	POST:
	//		m_threadAttribute has been initialized to default values
	//				
	attribute::attribute()
	{
		pthread_attr_init(&m_threadAttribute);
		m_scheduleParameter.sched_priority = 0;

	} // ThreadAttribute

	// ~ThreadAttribute:
	//	POST:
	//		Clean up has been performed
	//
	attribute::~attribute()
	{
		pthread_attr_destroy(&m_threadAttribute);
	} // ~ThreadAttribute

	// ThreadAttribute:
	//	Copy Constructor
	//	PRE:
	//		rhs := valid ThreadAttribute
	//	POST:
	//		m_threadAttribute == rhs.m_threadAttribute && !(m_threadAttribute === rhs.m_threadAttribute)
	//
	attribute::attribute(const attribute& rhs)
	{
		pthread_attr_init(&m_threadAttribute);
		if(rhs.isScheduleFifo())
			this->setScheduleFifo(rhs.getSchedulePriority());
		if(rhs.isScheduleRegular()) 
			this->setScheduleRegular();
		if(rhs.isScheduleRoundRobin()) 
			this->setScheduleRoundRobin();
		if(rhs.getDetachState()) 
			this->setCreateDetached();
		if(this->isScheduleFifo() || this->isScheduleRoundRobin())
			setSchedulePriority(rhs.getSchedulePriority());
		m_scheduleParameter.sched_priority = rhs.m_scheduleParameter.sched_priority;
	} // ThreadAttribute

	////////////////////////////////////////////////////////////////////////////////////////
	// Operators
	////////////////////////////////////////////////////////////////////////////////////////

	// operator ==
	//	PRE:
	//		rhs := valid ThreadAttribute 
	//	RET:
	//		iff(m_threadAttribute == rhs.m_threadAttribute) true else false		
	//
	bool attribute::operator==(const attribute& rhs) const
	{
		// Not Implemented
		NotImplementedException exp;
		throw exp;
	/* 	int thisValue = 0;
		int rhsValue = 0; 
		int returnValue = 0;

		// Detach State
		if(0 != (returnValue = pthread_attr_getdetachstate(&m_threadAttribute, thisValue)) 
		{
			throw 0;
		} 
		if(0 != (returnValue = pthread_attr_getdetachstate(&rhs.m_threadAttribute, rhsValue)) 
		{
			throw 0;
		} 
		if(thisValue != rhsValue) return false;

		// Schedule Policy
		if(0 != (returnValue = pthread_attr_getschedpolicy(&m_threadAttribute, thisValue)) 
		{
			throw 0;
		} 
		if(0 != (returnValue = pthread_attr_getschedpolicy(&rhs.m_threadAttribute, rhsValue)) 
		{
			throw 0;
		} 
		if(thisValue != rhsValue) return false;

		// Schedule Param
		//int (const pthread_attr_t *attr, struct sched_param *param);
		struct sched_param thisScheduleParam, rhsScheduleParam;

		if(0 != (returnValue = pthread_attr_getschedparam(&m_threadAttribute, &thisScheduleParam)) 
		{
			throw 0;
		} 
		if(0 != (returnValue = pthread_attr_getschedparam(&rhs.m_threadAttribute, &rhsScheduleParam)) 
		{
			throw 0;
		} 
		if(thisScheduleParam != rhsScheduleParam) return false;
	
		// Inherited Schedule
		if(0 != (returnValue = pthread_attr_getinheritsched(&m_threadAttribute, thisValue)) 
		{
			throw 0;
		} 
		if(0 != (returnValue = pthread_attr_getinheritsched(&rhs.m_threadAttribute, rhsValue)) 
		{
			throw 0;
		} 
		if(thisValue != rhsValue) return false;
	
		// Scope
		if(0 != (returnValue = pthread_attr_getscope(&m_threadAttribute, thisValue)) 
		{
			throw 0;
		} 
		if(0 != (returnValue = pthread_attr_getscope(&rhs.m_threadAttribute, rhsValue)) 
		{
			throw 0;
		} 
		if(thisValue != rhsValue) return false;

	*/
		return false;
	} // operator==

	// operator ==
	//	PRE:
	//		rhs := valid ThreadAttribute 
	//	RET:
	//		iff(m_threadAttribute == rhs.m_threadAttribute) true else false		
	//
	bool attribute::operator==(const pthread_attr_t& rhs) const
	{
		// Not Implemented
		NotImplementedException exp;
		throw exp;
		return &m_threadAttribute == &rhs;
	} // operator==

	const attribute& attribute::operator=(const attribute& rhs)
	{
		pthread_attr_destroy(&m_threadAttribute);
		pthread_attr_init(&m_threadAttribute);
		if(rhs.isScheduleFifo())
			this->setScheduleFifo(rhs.getSchedulePriority());
		if(rhs.isScheduleRegular()) 
			this->setScheduleRegular();
		if(rhs.isScheduleRoundRobin()) 
			this->setScheduleRoundRobin();
		if(rhs.getDetachState()) 
			this->setCreateDetached();
		if(this->isScheduleFifo() || this->isScheduleRoundRobin())
			setSchedulePriority(rhs.getSchedulePriority());

		return *this;
	} // operator=

/**
 * Pthreads documentation indicates that the thread attribute should be considered opague, so not allowing direct copying here
 * @see man pthread_attribute_initialize
	const pthread_attr_t& ThreadAttribute::operator=(const pthread_attr_t& rhs)
	{
		// TODO: This should probably call something similar to the copy constructor
		pthread_attr_destroy(&m_threadAttribute);
		pthread_attr_init(&m_threadAttribute);
		if(rhs.isScheduleFifo())
			this->setScheduleFifo(rhs.getSchedulePriority());
		if(rhs.isScheduleRegular()) 
			this->setScheduleRegular();
		if(rhs.isScheduleRoundRobin()) 
			this->setScheduleRoundRobin();
		if(rhs.getDetachState()) 
			this->setCreateDetached();
		if(this->isScheduleFifo() || this->isScheduleRoundRobin())
			setSchedulePriority(rhs.getSchedulePriority());

		return m_threadAttribute;
	} // operator=
*/

	////////////////////////////////////////////////////////////////////////////////////////
	// Thread Creation State
	////////////////////////////////////////////////////////////////////////////////////////

	// setCreateJoinable:
	//	Create Thread so that it's resources are not freed until parent Thread calls join()
	void attribute::setCreateJoinable()
	{
		int returnValue = 0;
		switch(pthread_attr_setdetachstate(&m_threadAttribute, PTHREAD_CREATE_JOINABLE))
		{
			case EINVAL:
				InvalidThreadAttributeException exp;
				throw exp;
				break;
		} // switch
	} // setCreateJoinable

	// setCreateDetached:
	//	Create the Thread so that it's resources and execution are independent of Parent Thread
	void attribute::setCreateDetached()
	{
		int returnValue = 0;
		switch(pthread_attr_setdetachstate(&m_threadAttribute, PTHREAD_CREATE_DETACHED))
		{
			case EINVAL:
				InvalidThreadAttributeException exp;
				throw exp;
				break;
		} // switch
	} // setCreateDetached

	// getDetachState:
	bool attribute::getDetachState() const
	{
		int detachState = 0;
		pthread_attr_getdetachstate(&m_threadAttribute, &detachState);
		if(PTHREAD_CREATE_DETACHED == detachState) return true;
			else return false;
	
	} // getDetachState
	
	////////////////////////////////////////////////////////////////////////////////////////
	// Scheduling Policies
	// DEFAULT: setScheduleRegular()
	// NOTE: Only Regular scheduling policies are available to processes not running as root
	////////////////////////////////////////////////////////////////////////////////////////

	// setScheduleRegular:
	//	regular, non-realtime scheduling
	void attribute::setScheduleRegular()
	{
		int returnValue = 0;
		switch(pthread_attr_setschedpolicy(&m_threadAttribute, SCHED_OTHER))
		{
			case EINVAL:
				InvalidThreadAttributeException exp;
				throw exp;
				break;
		} // switch
	} // setScheduleRegular

	// isScheduleRegular:
	//	regular, non-realtime scheduling
	bool attribute::isScheduleRegular() const
	{
		int returnValue = 0;
		int schedulePolicy = 0;
		pthread_attr_getschedpolicy(&m_threadAttribute, &schedulePolicy);
		if(SCHED_OTHER == schedulePolicy) return true;
		else return false;
	} // isScheduleRegular

	// setScheduleRoundRobin:
	//	real-time, round robin scheduling
	void attribute::setScheduleRoundRobin(int priority)
	{
		int returnValue = 0;
		switch(pthread_attr_setschedpolicy(&m_threadAttribute, SCHED_RR))
		{
			case EINVAL:
				{	
					InvalidThreadAttributeException exp;
					throw exp;
				}
				break;
			case ENOTSUP:
				{
					ThreadScheduleInsufficientPermission exp("Must be Super User to use this scheduling mechanism");
					throw exp;
				}
				break;
		} // switch
		setSchedulePriority(priority);
	} // setScheduleRoundRobin

	// isScheduleRoundRobin:
	//	regular, non-realtime scheduling
	bool attribute::isScheduleRoundRobin() const
	{
		int returnValue = 0;
		int schedulePolicy = 0;
		pthread_attr_getschedpolicy(&m_threadAttribute, &schedulePolicy);
		if(SCHED_RR == schedulePolicy) return true;
		else return false;
	} // isScheduleRoundRobin

	// setScheduleFifo:
	//	real-time, First-in First-out scheduling
	void attribute::setScheduleFifo(int priority)
	{
		int returnValue = 0;
		switch(pthread_attr_setschedpolicy(&m_threadAttribute, SCHED_FIFO))
		{
			case EINVAL:
				{
					InvalidThreadAttributeException exp;
					throw exp;
				}
				break;
			case ENOTSUP:
				{
					ThreadScheduleInsufficientPermission exp("Must be Super User to use this scheduling mechanism");
					throw exp;
				}
				break;
		} // switch
		setSchedulePriority(priority);
	} // setScheduleFifo

	// isScheduleFifo:
	//	regular, non-realtime scheduling
	bool attribute::isScheduleFifo() const
	{
		int returnValue = 0;
		int schedulePolicy = 0;
		pthread_attr_getschedpolicy(&m_threadAttribute, &schedulePolicy);
		if(SCHED_FIFO == schedulePolicy) return true;
		else return false;
	} // isScheduleFifo

	// setSchedulePriority
	//	valid values: 0 - 99
	//	Sets the scheduling priority for the thread
	void attribute::setSchedulePriority(int priority)
	{
		if(isScheduleRegular() && 0 == priority)
		{
			InvalidThreadAttributeException exp("Scheduling must be Fifo or Round Robin to set priority");
			throw exp;
		} // if
		
		if(priority < 1 || priority > 99)
		{
			InvalidThreadAttributeException exp("Priority must be 1 - 99");
			throw exp;
		} // if
		
		m_scheduleParameter.sched_priority = priority;
		switch(pthread_attr_setschedparam(&m_threadAttribute, &m_scheduleParameter))
		{
			case EINVAL:
				InvalidThreadAttributeException exp("Priority must be 1 - 99");
				throw exp;
				break;
		} // switch
		
	} // setSchedulePriority
	
	// getSchedulePriority
	//	returns the current scheduling priority
	int attribute::getSchedulePriority() const
	{
		pthread_attr_getschedparam(&m_threadAttribute, &m_scheduleParameter);
		return m_scheduleParameter.sched_priority;
	} // getSchedulePriority

	// getScheduleParameter
	//	returns the scheduling parameter
	const sched_param& attribute::getScheduleParameter() const
	{
		return m_scheduleParameter;
	} // getScheduleParameter

	// setExplicitSchedule:
	void attribute::setExplicitSchedule()
	{
		int returnValue = 0;
		switch(pthread_attr_setinheritsched(&m_threadAttribute, PTHREAD_EXPLICIT_SCHED))
		{
			case EINVAL:
				InvalidThreadAttributeException exp;
				throw exp;
				break;
		} // switch
	} // setExplicitSchedule

	// setInheritParentSchedule:
	void attribute::setInheritParentSchedule()
	{
		int returnValue = 0;
		switch(pthread_attr_setinheritsched(&m_threadAttribute, PTHREAD_INHERIT_SCHED))
		{
			case EINVAL:
				InvalidThreadAttributeException exp;
				throw exp;
				break;
		} // switch
	} // setInheritParentSchedule

	////////////////////////////////////////////////////////////////////////////////////////
	//	Scope
	////////////////////////////////////////////////////////////////////////////////////////

	// setScopeSystem:
	//	NOTE: LinuxThreads only supports system scope at time of writing
	void attribute::setScopeSystem()
	{
		int returnValue = 0;
		switch(pthread_attr_setscope(&m_threadAttribute, PTHREAD_SCOPE_SYSTEM))
		{
			case EINVAL:
				{
					InvalidThreadAttributeException exp;
					throw exp;
				}
				break;
			case ENOTSUP:
				{
					InvalidThreadAttributeException exp("Not Supported");
					throw exp;
				}
				break;
		} // switch
	} // setScopeSystem
	
	// setScopeProcess:
	//	NOTE: LinuxThreads does not support process scope at time of writing
	void attribute::setScopeProcess()
	{
		int returnValue = 0;
		switch(pthread_attr_setscope(&m_threadAttribute, PTHREAD_SCOPE_PROCESS))
		{
			case EINVAL:
				{
					InvalidThreadAttributeException exp;
					throw exp;
				}
				break;
			case ENOTSUP:
				{
					InvalidThreadAttributeException exp("Not Supported");
					throw exp;
				}
				break;
		} // switch
	} // setScopeProcess
	
	// getAttribute:
	const pthread_attr_t& attribute::getAttribute() const
	{
		return m_threadAttribute;
	} // const getAttribute
} // archendale


