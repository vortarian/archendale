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

using namespace std;
using std::string;
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
			obj << data  << SocketObject::transmit;
			data = "";
			obj >> data;
			cout << "Read Data: " << data << endl;
		}

		{
			char data = 'a';
			cout << endl << "char : " << data << endl;
			obj << data << SocketObject::transmit;
			data = 0;
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
	try {
		InternetAddress addr = NameResolver::getAddress("localhost");
		INETSocket obj(addr, 5000);
		obj.connect();

		const int DATASIZE = 400000;
		int* sendData = new int[DATASIZE]; 
		int* recieveData = new int[DATASIZE]; 
		if(!sendData && !recieveData)
		{
			cerr << "Not enough memory for test" << endl;	
			return false;
		} // if
		for(int i = 0; i < DATASIZE; i++)
		{
			sendData[i] = i;
		} // for
			
		try {
			cout 	<< "Sending "
				<< float(DATASIZE) / 100000
				<< "K bytes of data" 
				<< endl;
			for(int i = 0; i < DATASIZE; i++)
			{
				obj << sendData[i];
			} // for

			obj << SocketObject::transmit;

			for(int i = 0; i < DATASIZE; i++)
			{
				obj >> recieveData[i];
			} // for
		} catch (OutOfMemoryException exp) {
			cerr << exp.why() << endl;
			return false;
		} // try 

		for(int i = 0; i < DATASIZE; i++)
		{
			if(sendData[i] != recieveData[i]) 
			{	
				cerr << "Data not equal: " << endl;
				cerr << "sendData[" << i << "] = " << sendData[i] << endl;
				cerr << "recieveData[" << i << "] = " << recieveData[i] << endl;
				return false;
			} // if
		} // for
		delete sendData;
		delete recieveData;
	} catch (...) {
		cerr << "Caught Unknown exception in testSocketObjectLargeReadWrite" << endl;
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

void main(void)
{
	char input[4];
	do	
	{
		cout << endl << "Please input Command:" << endl <<
			"1: NameResolver\n"
			"2: SocketObject(Reads & Writes)\n"
			"3: SocketObject(Large Reads & Writes)\n"
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
			case 'q':
			case 'Q':
				break;
			default:
				cout << endl << "Unknown Command" << endl;
			} // switch
		} catch (...) {
			cerr << "caught unknown exception in MAIN" << endl;
		} // try
	} while(input[0] != 'q' && input[0] != 'Q');
} // main
