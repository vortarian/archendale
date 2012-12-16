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
		socket << data << '\0' << Socket::transmit;
		socket.getline(rdata, '\0');
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
