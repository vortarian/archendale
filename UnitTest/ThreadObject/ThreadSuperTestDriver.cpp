#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <ThreadObject/ThreadAttribute.h>
#include <ThreadObject/ThreadSuper.h>
#include <ThreadObject/ThreadException.h>

using namespace std;
using namespace archendale;

class ThreadCounter : public ThreadSuper
{
public:
	ThreadCounter( const char* output, int iterations = 1000);
	void count(); 
	void run();
private:
	int m_counter, m_iterations;
	char m_output[100];
};

void ThreadCounter::run()
{
	count();
} // run


ThreadCounter::ThreadCounter(const char* output, int iterations = 1000)
{
	ThreadAttribute attr;
	try
	{
		attr.setCreateDetached();
	} catch(int i)
	{
		cerr << "Caught: " << i << endl;
	} catch(...)
	{
		cerr << "Caught unknown exception" << endl;
	} // try
	
	setAttribute(attr);
	m_counter = 0;
	m_iterations = iterations;
	strcpy(m_output, output);
}

void ThreadCounter::count()
{
	cout << "ThreadCounter(" << getThread() << "): " << this << endl;
	for(m_counter; m_counter < m_iterations; m_counter++)
	{
		sleep(rand() % 10);
		cout << m_output << std::flush;
	}
}

void main(void)
{
	char test[50];
	ThreadCounter first("E", 10);
	ThreadCounter second("U", 10);
	ThreadCounter third("G", 40);
	ThreadCounter forth("T", 30);
	ThreadCounter fifth("Z", 10);
	
	first.start();
	second.start();
	third.start();
	forth.start();
	fifth.start();

	sleep(30);	
	try
	{
		first.join();
	}catch (ThreadDetachedException exp)
	{
		cerr << "Caught Exception: " << endl;
		perror("First");
	}
	try
	{
		second.join();
	}catch (ThreadDetachedException exp)
	{
		cerr << "Caught Exception: " << endl;
		perror("Second");
	}
	try
	{
		third.join();
	}catch (ThreadDetachedException exp)
	{
		cerr << "Caught Exception: " << endl;
		perror("third");
	}
	try
	{
		forth.join();
	}catch (ThreadDetachedException exp)
	{
		cerr << "Caught Exception: " << endl;
		perror("forth");
	}
	try
	{
		fifth.join();
	}catch (ThreadDetachedException exp)
	{
		cerr << "Caught Exception: " << endl;
		perror("Fifth");
	}
}
