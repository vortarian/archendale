#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>

#include <socket/name_resolver.h>
#include <socket/internet_address.h>
#include <socket/exception.h>
#include <socket/socket.h>
#include <socket/inet.h>
#include <socket/server.h>
#include <thread/thread.h>
#include <thread/mutex.h>

using namespace std;
using namespace archendale;
//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

const unsigned int NUM_WORKERS = 4;

class Worker : public Thread
{
public:
	Worker() { m_socketSet = false; }
	void setSocket(inet& sock) 
	{ 
		auto_mutex aMutex(mut);
		m_socket = sock; 
		m_socketSet = true;
	} // setSocket

	void run()
	{
		auto_mutex aMutex(mut);
		if(m_socketSet == false) 
		{
			std::cerr << "(Worker # " 
				<< this 
				<< ") Socket Not set before call to run, exiting" 
				<< endl;
			return;
		} // if

		try
		{
			string filename;

			m_socket.getline(filename, '\0');
			ofstream ostr(filename.c_str());
			if(!ostr)
			{
				string error = "Could not open ";
				error += filename;
				error += " for writing";
				m_socket << error << '\0';

				Exception exp(error);
				throw exp;
			} else
			{
				m_socket << "SendData" << '\0' 
					<< socket::transmit;

				cout << "(Worker # " 
					<< this 
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
			m_socket << "SendGood" << '\0' << socket::transmit;
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
			m_socket << error.str() << '\0' << socket::transmit;
			m_socketSet = false;
		} // try
		m_socketSet = false;
		return;
	} // run

private:
	mutex mut;
	inet m_socket;
	bool m_socketSet;
}; // Worker

static unsigned int workerNumber = 0;
unsigned int getNextWorkerNumber()
{
	workerNumber++;
	if(workerNumber == NUM_WORKERS) workerNumber = 0;
	return workerNumber;
} // getNextWorker

int main(int argc, char** argv)
{
	Worker *workers = new Worker[4];

	try {
		int port = 8000;
		string hostName = "localhost";	
		if(argc > 2)
		{
			if(argv[1][0] > '0' && argv[1][0] < '9') 
			{
				cerr << "Invalid host name specified: " << argv[1] << endl;
				cerr << "Usage: " << argv[0] << " <host> <port>" << endl;
				Exception exp("Invalid Host Name specified" + hostName);
				throw exp;
			} // if
			hostName = argv[1];
		} // if
		if(3 == argc)
		{
			int port = atoi(argv[2]);
			if(0 >= port) 
			{
				cerr << "Invalid port number specified: " << argv[2] << endl;
				cerr << "Usage: " << argv[0] << " <host> <port>" << endl;
				Exception exp("Invalid port specified");
				throw exp;
			} // if
		} // if
		internet_address addr = name_resolver::getAddress(hostName);
		server sserver(addr, port, 1);
		cout << "Server listening on " << hostName << ":" << port << endl;
		while(1)
		{
			cout << "Waiting for connection" << endl;
			inet socket = sserver.getWaitingConnection();
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

