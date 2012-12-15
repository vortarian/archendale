#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <string>
#include <typeinfo>

#include <socket/NameResolver.h>
#include <socket/InternetAddress.h>
#include <socket/SocketException.h>
#include <socket/SocketObject.h>
#include <socket/INETSocket.h>

using namespace std;
using namespace archendale;

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

bool testNameResolver()
{
	char input[500];
	cout << "Enter HostName: ";
	cin.getline(input, 500);
	string hostName(input);
	cerr << "Testing host: " << hostName << endl;	

	try
	{
		InternetAddress address = NameResolver::getAddress(hostName);
		vector < string > vec = address.getAddresses();
		vector < string >::const_iterator start = vec.begin();
		vector < string >::const_iterator end = vec.end();
		while(start != end)
		{
			cout << "Inet Address: ";
			cout << *start << endl;
			start++;
		} // while
		
		vec = address.getHostNames();
		start = vec.begin();
		end = vec.end();
		
		if(start != end) cout << "HostName: " << *start++ << endl;
		while(start != end) cout << "Alias: " << *start++ << endl;
	} catch (UnknownHostException exp)
	{
		cerr << "Host unknown: " << exp.why() << endl;
	} catch (RetryHostLookupException exp)
	{
		cerr << "Retry Host Exception on host: " << exp.why() << endl;
	} catch (HostWithNoAddressException exp)
	{
		cerr << "Host " << exp.why() << " does not have an associated IP" << endl;
	} catch (Exception exp)
	{
		cerr << "Unknown exception caught in host lookup" << endl;
	} // try

	return true;
} // testNameResolver

bool testSocketObjectRead()
{
	InternetAddress addr = NameResolver::getAddress("localhost");
	INETSocket obj(addr, 7);
	obj.connect();

	try {
		{
			string data = "testget"; 
			cout << endl << "string : " << data << endl;
			obj << data << '\0' << Socket::transmit;
			data = "";
			obj.getline(data, '\0');
			cout << "Read Data: " << data << endl;
		}

		{
			char data = 'a';
			cout << endl << "char : " << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			unsigned char data = 'a';
			cout << endl << "unsigned char :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			char data[] = "1234567890abcd";
			cout << endl << "char [15] :" << data << endl;
			obj << data << '\0' << Socket::transmit;
			string sdata;
			obj.getline(sdata, '\0');
			cout << "Read Data: " << sdata << endl;
		}

		{
			unsigned char data[15] = "1234567890abcd";
			cout << endl << "unsigned char[15] :" << data << '\0' << endl;
			obj << (char*) data << '\0' << Socket::transmit;
			string sdata;
			obj.getline(sdata, '\0');
			cout << "Read Data: " << sdata << endl;
		}

		{
			int data = 1234567890;
			cout << endl << "int :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			unsigned int data = 1234567890;
			cout << endl << "unsigned int :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			double data = 452462408;
			cout << endl << "double :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			long data = 452462408;
			cout << endl << "long :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			unsigned long data = 452462408;
			cout << endl << "unsigned long :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			float data = 234552.43;
			cout << endl << "float :" << data << endl;
			obj << data << Socket::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}
	} catch (OutOfMemoryException exp) {
		cerr << exp.why() << endl;
		return false;
	} catch (Exception& exp) 
	{
		// Catch any exceptions, report and swallow them
		std::cerr << "Unknown Exception caught: " << endl
			<< "type: " << typeid(exp).name() << endl
			<< "why: " << exp.why() << endl;
	} catch (...) {
		cerr << "Unknown Exception caught in testSocketObject" << endl;
		return false;
	} // try 

	return true;
} // testSocketObject

bool testSocketObjectLargeReadWrite(unsigned int dataSize = 4000000)
{
	try {
		InternetAddress addr = NameResolver::getAddress("localhost");
		int port = 5000;
		INETSocket obj(addr, port);
		try
		{
			obj.connect();
		} catch (ConnectionRefusedException exp)
		{
			cerr << "Connection to port " << port << " was refused, is the SocketServerTest running?" << endl;
			return false;
		} // try

		unsigned int DATASIZE = dataSize;

		char *p_data = new char[DATASIZE];

		cout << "Building Data, may take a few seconds" << endl;
		for(unsigned int i = 0; i < DATASIZE; i++)
		{
			// Can't send char == 0, as that is the delimiter for strings
			if(char(i) == char(0))
			{
				p_data[i] = char(i+1);
			} else
			{
				p_data[i] = char(i);
			} // if
		} // for
		// Set the terminator
		p_data[DATASIZE - 1] = '\0';	

		string sendData = p_data;	
		delete p_data;

		string receiveData;

		try {
			cout 	<< "Sending "
				<< (float(sendData.size()) * sizeof(string::size_type)) / 1024.0
				<< "K bytes of data" 
				<< endl;

			obj << sendData << '\0' << Socket::transmit;

			cout << "Data sent, reading data back" << endl;
			obj.getline(receiveData, '\0');

		} catch (OutOfMemoryException exp) 
		{
			cerr << exp.why() << endl;
			return false;
		} // try 

		if(sendData != receiveData) 
		{
			std::cerr << "sendData != receiveData" << endl;
			return false;
		} // if
	} catch (Exception& exp) 
	{
		// Catch any exceptions, report and swallow them
		std::cerr << "Unknown Exception caught: " << endl
			<< "type: " << typeid(exp).name() << endl
			<< "why: " << exp.why() << endl;

		return false;
	}
	return true;
} // testSocketObjectLargeReadWrite

void outputStatus(bool status) 
{
	if(!status)
		cerr << endl << "***********************************TEST FAILED***********************************" << endl;
	else
		cout << endl << "***********************************TEST SUCCEEDED********************************" << endl;
} // outputStatus

int main(void)
{
	char input[4];
	unsigned int datasize = 0;
	do	
	{
		cout << endl << "Please input Command:" << endl <<
			"1: NameResolver\n"
			"2: SocketObject(Reads & Writes)\n"
			"3: SocketObject(Large Reads & Writes - requires SocketServerTest to be running on port 5000)\n"
			"4: SocketObjectWithDataSpecified(Large Reads & Writes - requires SocketServerTest to be running on port 5000)\n"
			"Q: Quit\n"
			"?: ";
		cin.getline(input, 4);
		try 
		{
			switch(input[0]) 
			{
			case '1':	
				outputStatus(testNameResolver());
				break;
			case '2':	
				outputStatus(testSocketObjectRead());
				break;
			case '3':	
				outputStatus(testSocketObjectLargeReadWrite());
				break;
			case '4':	
				cout << "Please input number of Kbytes to use: ";
				cin >> datasize;
				datasize *= (1024/sizeof(string::size_type));
				outputStatus(testSocketObjectLargeReadWrite(datasize));
				// eatwhitespace
				cin.getline(input, 4);
				break;
			case 'q':
			case 'Q':
				break;
			default:
				cout << endl << "Unknown Command" << endl;
			} // switch
		} catch (Exception& exp) 
		{
			// Catch any exceptions, report and swallow them
			std::cerr << "Unknown Exception caught: " << endl
				<< "type: " << typeid(exp).name() << endl
				<< "why: " << exp.why() << endl;
		} catch (...) 
		{
			cerr << "caught unknown exception in MAIN" << endl;
		} // try
	} while(input[0] != 'q' && input[0] != 'Q');
} // main
