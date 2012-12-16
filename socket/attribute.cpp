#include <iostream>
#include "attribute.h"

using namespace std;

namespace archendale 
{
	attribute::attribute(unsigned int port, string host = "localhost")
	{
		cout << "SocketAttribute(port, host) Constructor Stub" << endl;
	} // SocketAttribute

	attribute::attribute(string portName, string host = "localhost")
	{
		cout << "SocketAttribute(portName, host) Constructor Stub" << endl;
	} // SocketAttribute(portName, host)

	attribute::~attribute() 
	{
		cout << "~SocketAttribute" << endl;
	} // ~SocketAttribute

	// setPort
	//      sets the port the host will listen on
	void setPort(unsigned int)
	{
		cout << "setPort" << endl;
	} // setPort

	// setPort
	//      sets the port the host will listen on by a port name
	void setPort(string portName)
	{
		cout << "setPort" << endl;
	} // setPort
} // archendale
