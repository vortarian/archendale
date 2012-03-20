#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <string>
#include <typeinfo>

#include <SocketObject/NameResolver.h>
#include <SocketObject/InternetAddress.h>
#include <SocketObject/SocketException.h>
#include <SocketObject/SocketObject.h>
#include <SocketObject/INETSocket.h>
#include <SocketObject/SocketServer.h>
#include <ThreadObject/ThreadSuper.h>
#include <ThreadObject/Mutex.h>
#include <ThreadObject/AutoMutex.h>

using namespace std;
using std::string;
using namespace archendale;

class Worker : public ThreadSuper
{
public:
	Worker() { m_socketSet = false; }
	void setSocket(INETSocket& sock) 
	{ 
		AutoMutex aMutex(mut);
		m_socket = sock; 
		m_socketSet = true;
	} // setSocket

	void run()
	{
		AutoMutex aMutex(mut);
		if(m_socketSet == false) 
		{
			std::cerr << "(Worker # " << this << ") Socket Not set before call to run, exiting" << endl;
			return;
		} // if

		string data;
		cout << "(Worker # " << this << ") - Waiting for data" << endl;	
		try 
		{
			m_socket.getline(data, '\0');
		} catch (InvalidDescriptorException& exp) 
		{
			cerr << "InvalidDescriptorException	caught: " << exp.why() << endl;
		} catch (NotConnectedException& exp) 
		{
			cerr << "NotConnectedException exp: " << exp.why() << endl;
		} catch (OperationWillBlockException exp) 
		{
			cerr << "OperationWillBlockException exp: " << exp.why() << endl;
		} catch (SignalException& exp) 
		{
			cerr << "SignalException exp: " << exp.why() << endl;
		} catch (InvalidArgumentException exp) 
		{
			cerr << "InvalidArgumentException exp: " << exp.why() << endl;
		} catch (SocketException& exp) 
		{
			cerr << "SocketException exp: " << exp.why() << endl;
		} // try

		if(data.size() < 255) 
		{
			cout << "Returning: " << data << endl;
		} else
		{
			string tempData(data, 0, 255);

			cout	<< "Data too large for display "
				<< "Sending "
				<< float(data.size()) / 100000
				<< "K bytes of data"
				<< endl;

			cout << "(Only displaying first 255 bytes of data!)" << endl;
			cout << "Returning: " << tempData << endl;
		} // if
		m_socket << data << '\0' << SocketObject::transmit;
		m_socketSet = false;
	} // run

private:
	Mutex mut;
	INETSocket m_socket;
	bool m_socketSet;
}; // Worker

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

const unsigned int NUM_WORKERS = 4;

static unsigned int workerNumber = 0;
unsigned int getNextWorkerNumber()
{
	workerNumber++;
	if(workerNumber == NUM_WORKERS) workerNumber = 0;
	return workerNumber;
} // getNextWorker

main(int argc, char** argv)
{

	Worker *workers = new Worker[4];

	try {
		int port = 5000;
		
		if(2 == argc)
		{
			int port = atoi(argv[1]);
			if(0 >= port) 
			{
				cerr << "Invalid port number specified" << endl;
			} // if
		} // if

		InternetAddress addr = NameResolver::getAddress("localhost");
		SocketServer sserver(addr, port, 1);

		while(1)
		{
			cout << "Waiting for connection" << endl;
			INETSocket socket = sserver.getWaitingConnection();
			unsigned int theWorkerNum = getNextWorkerNumber();
			cout << "Using worker: " << theWorkerNum << endl;
			// Could do this more intelligently, but it is only a unit test
			try
			{
				if(workers[theWorkerNum].isRunning()) workers[theWorkerNum].join();
			} catch(ThreadDetachedException& exp)
			{
				std::cerr << "Thread is detached, can not be joined, exiting" << endl;
				return -1;
			} // try
			workers[theWorkerNum].setSocket(socket);	
			workers[theWorkerNum].start();
		} // while
	} catch (SocketException& exp)
	{
	       std::cerr << "Unknown SocketException caught: " << endl
			<< "type: " << typeid(exp).name() << endl
			<< "why: " << exp.why() << endl;
	} catch (Exception& exp)
	{
	       std::cerr << "Unknown Exception caught: " << endl
			<< "type: " << typeid(exp).name() << endl
			<< "why: " << exp.why() << endl;
	} catch (...) 
	{
		cerr << "Caught Unknown Exception, aborting" << endl;
	} // try
	delete[] workers;
} // main










