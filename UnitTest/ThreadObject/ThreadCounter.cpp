#include <iostream>
#include <pthread.h>
#include "ThreadCounter.h"

ThreadCounter::ThreadCounter(const char* output, ThreadAttribute attr, int iterations = 1000, bool* finished = 0)
{
	mp_finished = finished;
        setAttribute(attr);
        m_counter = 0;
        m_iterations = iterations;
        strcpy(m_output, output);
} // ThreadCounter Constructor

void ThreadCounter::run()
{
	ThreadSuper::wait(2);
        count();
} // run

void ThreadCounter::count()
{
	if(mp_finished) *mp_finished = false;
        for(m_counter; m_counter < m_iterations; m_counter++)
        {
		ThreadSuper::wait(1);
                std::cout << m_output << std::flush;
		pthread_testcancel();
        }
	if(mp_finished) *mp_finished = true;
} // count


