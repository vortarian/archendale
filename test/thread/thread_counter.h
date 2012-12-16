#ifndef THREADCOUNTER_H
#define THREADCOUNTER_H

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <thread/thread.h>
#include <thread/attribute.h>

using archendale::Thread;
using archendale::ThreadAttribute;

class ThreadCounter : public Thread
{
public:
        ThreadCounter( const char*, const ThreadAttribute&, int iterations = 1000, bool* = 0);
        virtual ~ThreadCounter() { ; }
        void count();
        void run();
private:
        int m_counter, m_iterations;
        char m_output[100];
	bool* mp_finished;
}; // class ThreadCounter

#endif // THREADCOUNTER_H
