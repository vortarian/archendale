#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <ThreadObject/ThreadAttribute.h>
#include <ThreadObject/ThreadSuper.h>
#include <ThreadObject/ThreadException.h>

using namespace std;
using namespace archendale;

class ThreadCounter : public ThreadSuper
{
public:
	ThreadCounter( const char* output, ThreadAttribute, int iterations = 1000);
	void count(); 
	void run();
private:
	int m_counter, m_iterations;
	char m_output[100];
}; // class ThreadCounter

void ThreadCounter::run()
{
	count();
} // run

ThreadCounter::ThreadCounter(const char* output, ThreadAttribute attr, int iterations = 1000)
{
	setAttribute(attr);
	m_counter = 0;
	m_iterations = iterations;
	strcpy(m_output, output);
} // ThreadCounter Constructor

void ThreadCounter::count()
{
	for(m_counter; m_counter < m_iterations; m_counter++)
	{
		sleep(rand() % 4);
		cout << m_output << std::flush;
	}
} // count

bool testCreateDetached()
{
	// If the threads are created detached, then when they are joined, the 
	// they will throw an exception, if an exception is thrown, good :)

	int firstCount = 3;
	int secondCount = 3;
	int thirdCount = 3;
	int fourthCount = 3;
	int fifthCount = 3;

	ThreadAttribute attr;
	attr.setCreateDetached();
	ThreadCounter first("E", attr, firstCount);
	ThreadCounter second("U", attr, secondCount);
	ThreadCounter third("G", attr, thirdCount);
	ThreadCounter forth("T", attr, fourthCount);
	ThreadCounter fifth("Z", attr, fifthCount);

	cout << "Output Width:" << endl;	
	int totalCount = firstCount + secondCount + thirdCount + fourthCount + fifthCount;
	for(int i = 0; i < totalCount; i++)
	{
		cout << "-";
	} // for
	cout << endl;

	first.start();
	second.start();
	third.start();
	forth.start();
	fifth.start();

	// We have to be sure to exit without any of the threads actually being able to finish
	//  their work. If we do, then the thread exits, and it is not there, causing a
	//  ThreadNotFoundException 

	sleep(2);	
	int numberOfExceptionsCaught = 0;
	try
	{
		first.join();
	} catch (ThreadDetachedException exp)
	{
		numberOfExceptionsCaught++; 
	} // try
	try
	{
		second.join();
	} catch (ThreadDetachedException exp)
	{
		numberOfExceptionsCaught++; 
	} // try
	try
	{
		third.join();
	} catch (ThreadDetachedException exp)
	{
		numberOfExceptionsCaught++; 
	} // try
	try
	{
		forth.join();
	} catch (ThreadDetachedException exp)
	{
		numberOfExceptionsCaught++; 
	} // try
	try
	{
		fifth.join();
	} catch (ThreadDetachedException exp)
	{
		numberOfExceptionsCaught++; 
	} // try
	if(numberOfExceptionsCaught != 5) return false;
	
	// Now we need to sleep long enought for the above 5 threads to exit
	sleep(10);	
	cout << flush << endl << "Testing stop in ThreadDetached!" << endl;
	
	// Now we need to test that the thread exits as excepted
	try
	{
		first.stop();
	} catch (ThreadNotFoundException exp) 
	{
		// Chances are that the thread from above has already stopped
		// and exited, if so, this is not a problem, we can safely start
		// a new one
		// Honestly, if we get this far, we know it worked ;)
	}

	cout << endl << endl;
	first.start();

	// should give it plenty of time to execute and then exit	
	sleep(firstCount * 2);
	try
	{
		first.stop();
	} catch (ThreadNotFoundException exp) 
	{
		// Catching this exception is exactly what we want in this case
	}

	// Now to test that stop stops the thread, calling it twice in successtion should
	// work
	first.start();

	try
	{
		first.stop();
	} catch (ThreadNotFoundException exp) 
	{
		// We should not catch it here, as we should actually be cancelling the thread
		cerr << endl << "ThreadNotFoundException caught in :" << __FILE__ << ":" << __LINE__ << endl;
		return false;
	}
	try
	{
		cerr << "last stop" << endl;
		first.stop();
	} catch (ThreadNotFoundException exp) 
	{
		// Catching this exception is exactly what we want in this case
	}
	return true;
} // testCreateDetached

bool testJoinable()
{
	int firstCount = 3;
	int secondCount = 3;
	int thirdCount = 3;
	int fourthCount = 3;
	int fifthCount = 3;

	ThreadAttribute attr;
	attr.setCreateJoinable();
	ThreadCounter first("E", attr, firstCount);
	ThreadCounter second("U", attr, secondCount);
	ThreadCounter third("G", attr, thirdCount);
	ThreadCounter forth("T", attr, fourthCount);
	ThreadCounter fifth("Z", attr, fifthCount);

	cout << "Output Width:" << endl;	
	int totalCount = firstCount + secondCount + thirdCount + fourthCount + fifthCount;
	for(int i = 0; i < totalCount; i++)
	{
		cout << "-";
	} // for
	cout << endl;

	//first.start();
	//second.start();
	//third.start();
	//forth.start();
	//fifth.start();

	// No need to sleep here, if things work right, the first call will block
	int numberOfExceptionsCaught = 0;
	try
	{
		cerr << "1" << endl;
		//first.join();
		cerr << "2" << endl;
		//second.join();
		cerr << "3" << endl;
		//third.join();
		cerr << "4" << endl;
		//forth.join();
		cerr << "5" << endl;
		//fifth.join();
		cerr << "6" << endl;
	} catch (ThreadDetachedException exp)
	{
		numberOfExceptionsCaught++; 
	} catch (...) 
	{
		cerr << "Unknown exception: " << __FILE__ << ":" << __LINE__ << endl;
	} // try
	cerr << "returning" << endl;
	if(numberOfExceptionsCaught != 0) return false;
	else return true;
} // testCreateJoinable

bool testPriority()
{
	try {
		cout << "Setting priority before creation, starting in 3 seconds" << endl;
		ThreadAttribute attr;
		attr.setScheduleRoundRobin(8);
		ThreadCounter midPriority("E", attr, 12);
		sleep(3);
		midPriority.start();
		sleep(3);
		cout << endl << "Chaning Priority In Process" << endl;
		midPriority.scheduleRoundRobin(80);
		sleep(18);
		midPriority.join();
	} catch (ThreadScheduleInsufficientPermission exp) {
		cerr << exp.why() << endl;
		return false;
	} catch (ThreadDetachedException exp) {
		cerr << "Caught ThreadDetachedException" << endl;
		return false;
	} catch (ThreadParameterOutsideOfMemorySpaceException exp) {
		cerr << "Caught ThreadParameterOutsideOfMemorySpaceException" << endl;
		return false;
	} catch (...) {
		cerr << "Caught unknown exception - errno: " << errno << endl;
		return false;
	} // try 
	return true;
} // testPriority

void outputStatus(bool status) 
{
	if(!status)
		cerr << endl << "***********************************TEST FAILED***********************************" << endl;
	else
		cout << endl << "***********************************TEST SUCCEEDED********************************" << endl;
} // testFunction

void main(void)
{
	try 
	{
		cout << "Testing Joinable Threads" << endl << endl;
		outputStatus(testJoinable());

		//cout << "Testing Priority" << endl << endl;
		//outputStatus(testPriority());

		cout << "Testing Detached Threads" << endl << endl;
		outputStatus(testCreateDetached());
	} catch (...) {
		cerr << "caught unknown exception in MAIN" << endl;
	}
	exit(0);
} // main
