#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <ThreadObject/ThreadAttribute.h>
#include <ThreadObject/ThreadSuper.h>
#include <ThreadObject/ThreadException.h>
#include <ThreadObject/AutoMutex.h>
#include <ThreadObject/AutoMutexTry.h>
#include "ThreadCounter.h"
#include <UnitTest/ThreadObject/DetachedThreadRunner.h>
#include <typeinfo>

using namespace std;
using namespace archendale;

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

void displayWidth(unsigned int width = 0) {
    cout << "Output Width:" << endl;
    for (int i = 0; i < width; i++) cout << "-";
    cout << endl << flush;

} // displayWidth

// testDetached:
//	In a nutshell, the concept of detached is to create a
//	thread, and let it run to completion, not having
//	any resources cleaned up, even after the calling thread
//	has exited, thus, as long as the calling thread is
//	not the main thread, it should run to completion
//	without losing resources.  In this case, a thread is 
//	created by DetachedThreadRunner, and is run by the 
//	DetachedThreadRunner::run().  If this can happen, 
//	and the DetachedThreadRunner goes out of scope (is 
//	destroyed), and the thread created by DetachedThreadRunner
//	continues to operate, then we have accomplished the task
//	of a detached thread.  The way this works, is we give the 
//	pointer that will point to the new thread, and 
//	DetachedThreadRunner will create the new thread using
//	this pointer as a handle.  This is so we can be sure to 
//	do memory cleanup before exiting main.
//	In the future, this should be changed to use a 
//	strstream, so we can check the actual output and be sure 
//	the thread runs to completion.
ThreadCounter* pGlobalThreadCounter;

void runDetached(bool* finished) {
    DetachedThreadRunner runner1(pGlobalThreadCounter, finished);
    DetachedThreadRunner runner2(pGlobalThreadCounter, finished);
    DetachedThreadRunner runner3(pGlobalThreadCounter, finished);
    DetachedThreadRunner runner4(pGlobalThreadCounter, finished);
    DetachedThreadRunner runner5(pGlobalThreadCounter, finished);
    runner1.run();
    runner2.run();
    runner3.run();
    runner4.run();
    runner5.run();
} // runDetached

bool testDetached() {
    char input[4];
    bool isFinished = false;
    cout << "You should see 10 lines stating, \"Detached\" " << endl;
    runDetached(&isFinished);
    while (!isFinished);
    do {
        cout << "Did you see the line 10 times? (Y/N):";
        cin.getline(input, 4);
        switch (input[0]) {
            case 'y':
            case 'Y':
                return true;
                break;
            case 'n':
            case 'N':
                return false;
                break;
        }
    } while (1);
} // testDetached

bool testJoinable() {
    int count = 3;

    ThreadAttribute attr;
    attr.setCreateJoinable();
    ThreadCounter first("E", attr, count);
    ThreadCounter second("U", attr, count);
    ThreadCounter third("G", attr, count);
    ThreadCounter forth("T", attr, count);
    ThreadCounter fifth("Z", attr, count);

    displayWidth(count * 5);

    first.start();
    second.start();
    third.start();
    forth.start();
    fifth.start();

    int numberOfExceptionsCaught = 0;
    try {
        first.join();
        second.join();
        third.join();
        forth.join();
        fifth.join();
    } catch (ThreadDetachedException exp) {
        numberOfExceptionsCaught++;
    }
    if (numberOfExceptionsCaught == 0) return true;
	else return false;
} // testCreateJoinable

bool testPriority() {
    try {
        cout << "Setting priority before creation, starting in 3 seconds" << endl;
        ThreadAttribute attr;
        attr.setScheduleRoundRobin(8);
        ThreadCounter midPriority("E", attr, 40);
        displayWidth(40);
        midPriority.start();
        ThreadSuper::wait(2);
        cout << endl << "Chaning Priority In Process" << endl;
        midPriority.scheduleRoundRobin(80);
        ThreadSuper::wait(2);
        cout << endl << "Joining" << endl;
        midPriority.join();
    } catch (ThreadScheduleInsufficientPermission exp) {
        cerr << exp.why() << endl;
        return false;
    } catch (ThreadDetachedException exp) {
        cerr << "Caught ThreadDetachedException" << endl;
        return false;
    } catch (ThreadNotFoundException exp) {
        cerr << "Caught ThreadNotFoundException" << endl;
        return false;
    } catch (ThreadParameterOutsideOfMemorySpaceException exp) {
        cerr << "Caught ThreadParameterOutsideOfMemorySpaceException" << endl;
        return false;
    } catch (Exception& ex) {
        printf("Exception: [%s]\n\tWhy: [%s]\n", typeid (ex).name(), ex.why().c_str());
        return false;
    } catch (...) {
        cerr << "Caught unknown exception - errno: " << errno << endl;
        return false;
    } // try 
    return true;
} // testPriority

// testConstructionDestruction:
//	test the constructor of the thread and the various thread related classes
//	very simply, build all of them, and then call each destructor

bool testConstructionDestruction(void) {
    try {

        {
			ThreadAttribute attr;
			ThreadCounter first("E", attr, 1);
			Mutex mutex, mutex2;
			AutoMutex amutex(mutex);
			AutoMutexTry atmutex(mutex2);

			// TODO: In current GCC calling the destructor here is also causing a 2nd call of the destructor when the code block exits ... look into why ..
			// atmutex.~AutoMutexTry();
			// amutex.~AutoMutex();
			// mutex2.~Mutex();
			// mutex.~Mutex();
			// first.~ThreadCounter();
			// attr.~ThreadAttribute();
        }
    } catch (ThreadDetachedException exp) {
        cerr << "testConstructionDestruction: Caught ThreadDetachedException as Expected" << endl;
    } catch (Exception& ex) {
        printf("Exception: [%s]\n\tWhy: [%s]\n", typeid (ex).name(), ex.why().c_str());
		return false;
    } catch (...) {
        cerr << "testConstructionDestructionDetached: Caught Unknown Exception" << endl;
        return false;
    }
    return true;
}

void outputStatus(bool status) {
    if (!status)
        cerr << endl << "***********************************TEST FAILED***********************************" << endl;
    else
        cout << endl << "***********************************TEST SUCCEEDED********************************" << endl;
} // testFunction

int main(void) {
    char input[4];
    do {
        cout << endl << "Please input Command:" << endl <<
                "1: JoinableTest\n"
                "2: DetachedTest\n"
                "3: PriorityTest (Must be root)\n"
                "4: Construction/DestructionTest\n"
                "Q: Quit\n"
                "?:";
        cin.getline(input, 4);
        try {
            switch (input[0]) {
                case '1':
                    cout << endl << "Testing Joinable Threads" << endl << endl;
                    outputStatus(testJoinable());
                    break;
                case '2':
                    cout << endl << "Testing Detached Threads" << endl << endl;
                    outputStatus(testDetached());
                    break;
                case '3':
                    cout << endl << "Testing Priority" << endl << endl;
                    outputStatus(testPriority());
                    break;
                case '4':
                    cout << endl << "Testing Construction/Destruction" << endl << endl;
                    outputStatus(testConstructionDestruction());
                    break;
                case 'q':
                case 'Q':
                    break;
                default:
                    cout << endl << "Unknown Command" << endl;
            }
        } catch (Exception& ex) {
            cerr << "caught exception in MAIN" << endl;
            printf("Exception: [%s]\n\tWhy: [%s]\n", typeid (ex).name(), ex.why().c_str());
        } catch (...) {
            cerr << "caught unknown exception in MAIN" << endl;
        } // try
    } while (input[0] != 'q' && input[0] != 'Q');
    delete pGlobalThreadCounter;
} // main
