#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <string>
#include <sstream>

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
using namespace archendale;
//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

const unsigned int NUM_WORKERS = 4;

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
			std::cerr << "(Worker # " 
				<< int(this) 
				<< ") Socket Not set before call to run, exiting" 
				<< endl;
			return;
		} // if

		try
		{
			string filename;

			m_socket >> filename;
			ofstream ostr(filename.c_str());
			if(!ostr)
			{
				string error = "Could not open ";
				error += filename;
				error += " for writing";
				m_socket << error;

				Exception exp(error);
				throw exp;
			} else
			{
				m_socket << "SendData" 
					<< SocketObject::transmit;

				cout << "(Worker # " 
					<< int(this) 
					<< ") - File open, Waiting for data" 
					<< endl;	
			} // if
			size_t filesize;
			m_socket >> filesize;
			cout 	<< "Writing " 
				<< filesize 
				<< " bytes to " 
				<< filename 
				<< endl;
			char ch;
			for(size_t iCounter = 0; iCounter < filesize; iCounter++)
			{
				ch = m_socket.get();
				ostr.put(ch);
			} // for
			m_socket << "SendGood" << SocketObject::transmit;
			cout 	<< "Received " 
				<< m_socket.getBytesReceived() 
				<< " bytes, returning" 
				<< endl;	
		} catch (Exception& exp)
		{
			stringstream error;
			error << "Exception caught: " 
				<< endl
				<< "\ttype: " 
				<< typeid(exp).name() 
				<< endl
				<< "\twhy: " 
				<< exp.why() 
				<< endl;
			cerr << error.str() << endl;
			m_socket << error.str() << SocketObject::transmit;
			m_socketSet = false;
		} // try
		m_socketSet = false;
		return;
	} // run

private:
	Mutex mut;
	INETSocket m_socket;
	bool m_socketSet;
}; // Worker

static unsigned int workerNumber = 0;
unsigned int getNextWorkerNumber()
{
	workerNumber++;
	if(workerNumber == NUM_WORKERS) workerNumber = 0;
	return workerNumber;
} // getNextWorker

int main(char** argv, int argc )
{

	Worker *workers = new Worker[4];

	try {
		int port = 8000;
		
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
		cout << "Server listening on localhost:" << port << endl;
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
				throw exp;
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
	return 0;
} // main

