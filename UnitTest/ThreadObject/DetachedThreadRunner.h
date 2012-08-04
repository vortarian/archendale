#ifndef DETACHEDTHREADRUNNER_H
#define DETACHEDTHREADRUNNER_H

#include <ThreadObject/ThreadSuper.h>
#include <UnitTest/ThreadObject/ThreadCounter.h>

using archendale::Thread;

class DetachedThreadRunner : public Thread
{
public:
	// DetachedThreadRunner:
	//	ThreadCounter*& is the pointer used to hold the 
	//	instantiated version of ThreadCounter
	// 	bool& is a flag for the counter to set when done
	//	printing
	DetachedThreadRunner(ThreadCounter*&, bool*);
	~DetachedThreadRunner();
	void run();
private:
	ThreadCounter*& m_pThreadCounter;
	bool* mp_finished;
};

#endif // DETACHEDTHREADRUNNER_H
