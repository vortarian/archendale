#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <vector>

#include <SocketObject/NameResolver.h>

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
	cerr << "Testing host: " << hostName << endl;	
	NameResolver nr(hostName);
	vector < String > vec = nr.getAddress();
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
	
	vec = nr.getName();
	start = vec.begin();
	end = vec.end();
	
	if(start != end) cout << "HostName: " << *start++ << endl;
	while(start != end)
	{
		cout << "Alias: " << *start++ << endl;
	}
	return true;
} // testNameResolver

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
