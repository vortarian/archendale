#include <iostream>
#include <test/thread/DetachedThreadRunner.h>

DetachedThreadRunner::DetachedThreadRunner(ThreadCounter*& pThreadCounter, bool* bFinished) : Thread(), m_pThreadCounter(pThreadCounter), mp_finished(bFinished)
{
} // DetachedThreadRunner

DetachedThreadRunner::~DetachedThreadRunner() 
{
} // ~DetachedThreadRunner

void DetachedThreadRunner::run() 
{
	ThreadAttribute attr;
	// This builds the object, then starts it
	m_pThreadCounter = new ThreadCounter("Detached\n", attr, 2, mp_finished); 
	m_pThreadCounter->start();
} // run
