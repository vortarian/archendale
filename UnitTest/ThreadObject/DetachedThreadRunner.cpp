#include <UnitTest/ThreadObject/DetachedThreadRunner.h>

DetachedThreadRunner::DetachedThreadRunner(ThreadCounter*& pThreadCounter, bool* bFinished) : m_pThreadCounter(pThreadCounter), mp_finished(bFinished)
{
} // DetachedThreadRunner

DetachedThreadRunner::~DetachedThreadRunner()
{
	cerr << endl << "DetachedThreadRunner going out of scope" << endl;
} // ~DetachedThreadRunner

void DetachedThreadRunner::run() 
{
	ThreadAttribute attr;
	// This builds the object, then starts it
	m_pThreadCounter = new ThreadCounter("Detached\n", attr, 10, mp_finished); 
	m_pThreadCounter->start();
} // run
