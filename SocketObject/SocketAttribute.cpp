#include <iostream>
#include "SocketAttribute.h"

using namespace std;

namespace archendale 
{
	SocketAttribute::SocketAttribute(unsigned int port, String host = "localhost")
	{
		cout << "SocketAttribute(port, host) Constructor Stub" << endl;
	} // SocketAttribute

	SocketAttribute::SocketAttribute(String portName, String host = "localhost")
	{
		cout << "SocketAttribute(portName, host) Constructor Stub" << endl;
	} // SocketAttribute(portName, host)

	SocketAttribute::~SocketAttribute() 
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
	void setPort(String portName)
	{
		cout << "setPort" << endl;
	} // setPort
} // archendale
