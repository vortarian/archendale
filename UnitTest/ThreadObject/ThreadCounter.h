#ifndef THREADCOUNTER_H
#define THREADCOUNTER_H

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ThreadObject/ThreadSuper.h>
#include <ThreadObject/ThreadAttribute.h>

using archendale::ThreadSuper;
using archendale::ThreadAttribute;

class ThreadCounter : public ThreadSuper
{
public:
        ThreadCounter( const char* output, ThreadAttribute, int iterations = 1000, bool* = 0);
        ~ThreadCounter() { ; }
        void count();
        void run();
private:
        int m_counter, m_iterations;
        char m_output[100];
	bool* mp_finished;
}; // class ThreadCounter

#endif // THREADCOUNTER_H
