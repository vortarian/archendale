#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <typeinfo>

#include <unistd.h>
#include <errno.h>

#include <socket/name_resolver.h>
#include <socket/internet_address.h>
#include <socket/exception.h>
#include <socket/socket.h>
#include <socket/inet.h>
#include <socket/server.h>

using namespace std;
using std::string;
using namespace archendale;

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

main(int argc, char** argv)
{
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

		internet_address addr = name_resolver::getAddress("localhost");
		server sserver(addr, port, 1);

		while(1)
		{
			cout << "Waiting for connection" << endl;
			inet socket = sserver.getWaitingConnection();
			string data;
			cout << "Waiting for data" << endl;	
			try 
			{
				socket.getline(data, '\0');
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
			socket << data << '\0' << socket::transmit;
			cout << "Total bytes sent on this socket: " << socket.getBytesSent() << endl;
			cout << "Total bytes received on this socket: " << socket.getBytesReceived() << endl;
		} // while
	} catch (SocketException& exp)
	{
	       std::cerr << "Unknown SocketException caught: " << endl
			<< "type: " << typeid(exp).name() << endl
			<< "why: " << exp.why() << endl;
	} catch (...) 
	{
		cerr << "Caught Unknown Exception, aborting" << endl;
	} // try
} // main










