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

		cout << "Waiting for connection" << endl;
		INETSocket socket = sserver.getWaitingConnection();
		string data;
		cout << "Waiting for data" << endl;	
		try 
		{
			socket >> data;
		} catch (InvalidSocketDescriptorException exp) 
		{
			cerr << "InvalidSocketDescriptorException	caught: " << exp.why() << endl;
		} catch (SocketNotConnectedException exp) 
		{
			cerr << "SocketNotConnectedException exp: " << exp.why() << endl;
		} catch (OperationWillBlockException exp) 
		{
			cerr << "OperationWillBlockException exp: " << exp.why() << endl;
		} catch (SignalException exp) 
		{
			cerr << "SignalException exp: " << exp.why() << endl;
		} catch (InvalidArgumentException exp) 
		{
			cerr << "InvalidArgumentException exp: " << exp.why() << endl;
		} catch (Exception exp) 
		{
			cerr << "Exception exp: " << exp.why() << endl;
		} // try

		cout << "Recieved string data: " << data << endl;
		cout << "Returning: " << data << endl;
		socket << data << SocketObject::transmit;
		cout << "Done!" << endl;
	} catch (...) 
	{
		cerr << "Caught Unknown Exception, aborting" << endl;
	} // try
} // main










