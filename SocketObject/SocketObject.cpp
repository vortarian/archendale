#include <iostream>
#include "SocketObject.h"

using namespace std;

namespace archendale
{
	SocketObject::SocketObject(const SocketAttribute& attr)
	{
		cout << "SocketObject Constructor Stub " << endl;
		m_socketAttribute = attr;
	} // SocketObject
	
	SocketObject::SocketObject(const SocketObject& rhs)
	{
		cout << "SocketObject Copy Constructor Stub " << endl;
		m_socketAttribute = rhs.m_socketAttribute;
	} // SocketObject
	
	SocketObject& SocketObject::operator<<(const char* data) 
	{
		cout << "SocketObject::operator<< Stub " << endl;
		cout << data << endl;
		return *this;
	} // operator<<
	
	SocketObject& SocketObject::operator>>(const char* data) 
	{
		cout << "SocketObject::operator<< Stub " << endl;
		cout << data << endl;
		return *this;
	} // operator>>
} // archendale
