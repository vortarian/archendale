#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <vector>

#include <SocketObject/NameResolver.h>
#include <SocketObject/InternetAddress.h>
#include <SocketObject/SocketException.h>
#include <SocketObject/SocketObject.h>

using namespace std;
using namespace archendale;

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

union inetaddr
{
	char name[6];
	unsigned char uname[6];
	unsigned int i;
} test;

bool testNameResolver()
{
	char input[500];
	cout << "Enter HostName: ";
	cin.getline(input, 500);
	String hostName(input);
	InternetAddress address;
	address.addHostName(hostName);
	cerr << "Testing host: " << hostName << endl;	

	try
	{
		address = NameResolver::getAddress(address);
		vector < String > vec = address.getAddresses();
		vector < String >::const_iterator start = vec.begin();
		vector < String >::const_iterator end = vec.end();
		while(start != end)
		{
			test.uname[0] = start->data()[0];
			test.uname[1] = start->data()[1];
			test.uname[2] = start->data()[2];
			test.uname[3] = start->data()[3];
			cout << "Inet Address: ";
			cout << (int) test.uname[0] << ".";
			cout << (int) test.uname[1] << ".";
			cout << (int) test.uname[2] << ".";
			cout << (int) test.uname[3] << endl;
			start++;
		}
		
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

bool testSocketObject()
{
	SocketObject obj;

	{
		char data = 'a';
		cout << endl << "char :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		unsigned char data = 'a';
		cout << endl << "unsigned char :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		char data[] = "1234567890abcd";
		cout << endl << "char [15] :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		unsigned char data[15] = "1234567890abcd";
		cout << endl << "unsigned char[15] :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		int data = 1234567890;
		cout << endl << "int :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		unsigned int data = 1234567890;
		cout << endl << "unsigned int :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		double data = 452462408;
		cout << endl << "double :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		long data = 452462408;
		cout << endl << "long :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		unsigned long data = 452462408;
		cout << endl << "unsigned long :" << endl;
		obj << data << SocketObject::transmit;
	}

	{
		float data = 234552.43;
		cout << endl << "float :" << endl;
		obj << data << SocketObject::transmit;
	}

	return true;
} // testSocketObject

void outputStatus(bool status) 
{
	if(!status)
		cerr << endl << "***********************************TEST FAILED***********************************" << endl;
	else
		cout << endl << "***********************************TEST SUCCEEDED********************************" << endl;
} // outputStatus

void main(void)
{
	char input[4];
	do	
	{
		cout << endl << "Please input Command:" << endl <<
			"1: NameResolver\n"
			"2: SocketObject\n"
			"Q: Quit\n"
			"?:";
		cin.getline(input, 4);
		try 
		{
			switch(input[0]) 
			{
			case '1':	
				outputStatus(testNameResolver());
				break;
			case '2':	
				outputStatus(testSocketObject());
				break;
			case 'q':
			case 'Q':
				break;
			default:
				cout << endl << "Unknown Command" << endl;
			}
		} catch (...) {
			cerr << "caught unknown exception in MAIN" << endl;
		} // try
	} while(input[0] != 'q' && input[0] != 'Q');
} // main
