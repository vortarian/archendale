#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <string>

#include <SocketObject/NameResolver.h>
#include <SocketObject/InternetAddress.h>
#include <SocketObject/SocketException.h>
#include <SocketObject/SocketObject.h>
#include <SocketObject/INETSocket.h>
#include <SocketObject/SocketServer.h>

using namespace std;
using std::string;
using namespace archendale;

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

main(char** argv, int argc )
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

		InternetAddress addr = NameResolver::getAddress("localhost");
		SocketServer sserver(addr, port, 1);

		while(1)
		{
			cout << "Waiting for connection" << endl;
			INETSocket socket = sserver.getWaitingConnection();
			string data;
			cout << "Waiting for data" << endl;	
			try 
			{
				socket >> data;
			} catch (InvalidDescriptorException exp) 
			{
				cerr << "InvalidDescriptorException	caught: " << exp.why() << endl;
			} catch (NotConnectedException exp) 
			{
				cerr << "NotConnectedException exp: " << exp.why() << endl;
			} catch (OperationWillBlockException exp) 
			{
				cerr << "OperationWillBlockException exp: " << exp.why() << endl;
			} catch (SignalException exp) 
			{
				cerr << "SignalException exp: " << exp.why() << endl;
			} catch (InvalidArgumentException exp) 
			{
				cerr << "InvalidArgumentException exp: " << exp.why() << endl;
			} catch (SocketException exp) 
			{
				cerr << "SocketException exp: " << exp.why() << endl;
			} // try

			if(data.size() < 255) 
			{
				cout << "Returning: " << data << endl;
			} else
			{
				string tempData(data, 0, 255);
				cout << "Data too large for display, size is " << data.size() / 4 << " bytes" << endl;
				cout << "Only displaying first 255 bytes of data!" << endl;
				cout << "Returning: " << tempData << endl;
			} // if
			socket << data << SocketObject::transmit;
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










