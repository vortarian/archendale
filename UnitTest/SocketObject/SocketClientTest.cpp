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

main(char** argv, int argc)
{
	try 
	{
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
		string data, rdata;
		INETSocket socket(addr, port);

		cout << "Getting connection" << endl;
		socket.connect();

		cout << "Have Connection, enter data: " << endl;
		getline(cin, data);
		cout << "Sending: " << data << endl;
		socket << data << SocketObject::transmit;
		socket >> rdata;
		cout << "Recieved: " << rdata << endl;
		if(rdata == data) cout << "Succeeded!!!!!!!" << endl;
		else cout << "Failed!" << endl;
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
