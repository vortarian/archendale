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
#include <SocketObject/INETSocket.h>

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

bool testSocketObject()
{
	SocketObject obj;

	try {
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
			obj << (char*) data << SocketObject::transmit;
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
	} catch (OutOfMemoryException exp) {
		cerr << exp.why() << endl;
		return false;
	} // try 

	return true;
} // testSocketObject

bool testSocketObjectRead()
{
	INETSocket obj;
	obj.connect();

	try {
		{
			string data = "testget"; 
			cout << endl << "string : " << data << endl;
			obj << data  << SocketObject::transmit;
			data = "";
			cerr << endl << "Recieving" << endl;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			char data = 'a';
			cout << endl << "char : " << data << endl;
			obj << data << char(13) << SocketObject::transmit;
			data = 0;
			cerr << endl << "Recieving" << endl;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			unsigned char data = 'a';
			cout << endl << "unsigned char :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			char data[] = "1234567890abcd";
			cout << endl << "char [15] :" << data << endl;
			obj << data << SocketObject::transmit;
			string sdata;
			obj >> sdata;
			cout << "Read Data: " << sdata << endl;
		}

		{
			unsigned char data[15] = "1234567890abcd";
			cout << endl << "unsigned char[15] :" << data << endl;
			obj << (char*) data << SocketObject::transmit;
			string sdata;
			obj >> sdata;
			cout << "Read Data: " << sdata << endl;
		}

		{
			int data = 1234567890;
			cout << endl << "int :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			unsigned int data = 1234567890;
			cout << endl << "unsigned int :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			double data = 452462408;
			cout << endl << "double :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			long data = 452462408;
			cout << endl << "long :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			unsigned long data = 452462408;
			cout << endl << "unsigned long :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			float data = 234552.43;
			cout << endl << "float :" << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
			obj >> data;
			cout << "Read Data: " << data << endl;
		}
	} catch (OutOfMemoryException exp) {
		cerr << exp.why() << endl;
		return false;
	} catch (...) {
		cerr << "Unknown Exception caught in testSocketObject" << endl;
		return false;
	} // try 

	return true;
} // testSocketObject

bool testSocketObjectLargeReadWrite()
{
	INETSocket obj;
	obj.connect();
	int sendData[2000]; 
	int recieveData[sizeof(sendData) / sizeof(int)]; 
	if(sizeof(recieveData) != sizeof(sendData))
	{
		cerr << "Data Size is not equal, can not complete large send" << endl;
		return false;
	} // if
	for(int i = 0; i < sizeof(sendData) / sizeof(int); i++)
	{
		sendData[i] = i;
	} // for
		
	try {
		cout 	<< "Sending "
			<< float(sizeof(sendData)) / 100000
			<< "K bytes of data" 
			<< endl;

		for(int i = 0; i < sizeof(sendData) / sizeof(int); i++)
		{
			obj << sendData[i];
		} // for

		cout << "Transmitting" << endl;
		obj << SocketObject::transmit;
		cout << "Recieving" << endl;
		for(int i = 0; i < sizeof(recieveData) / sizeof(int); i++)
		{
			obj >> recieveData[i];
		} // for
	} catch (OutOfMemoryException exp) {
		cerr << exp.why() << endl;
		return false;
	} catch (...) {
		cerr << "Unknown Exception caught in testSocketObject" << endl;
		return false;
	} // try 

	for(int i = 0; i < sizeof(sendData) / sizeof(int); i++)
	{
		if(sendData[i] != recieveData[i]) 
		{	
			cerr << "Data not equal: " << endl;
			cerr << "sendData[" << i << "] = " << sendData[i] << endl;
			cerr << "recieveData[" << i << "] = " << recieveData[i] << endl;
			return false;
		} // if
	} // for
	return true;
} // testSocketObjectLargeReadWrite

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
			"3: SocketObject(Reads)\n"
			"4: SocketObject(Large Reads & Writes)\n"
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
			case '3':	
				outputStatus(testSocketObjectRead());
				break;
			case '4':	
				outputStatus(testSocketObjectLargeReadWrite());
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
