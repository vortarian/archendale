
#ifndef SOCKETOBJECT_H
#define SOCKETOBJECT_H

#include <sys/types.h>
#include <sys/socket.h>    
#include "SocketAttribute.h"

namespace archendale 
{
	class SocketObject 
	{
	public:
		SocketObject(const SocketAttribute&);
		SocketObject(const SocketObject&);

		SocketObject& operator<<(const char*); 
		SocketObject& operator>>(const char*);
	private:
		SocketAttribute m_socketAttribute;
	}; // SocketObject
} // archendale

#endif // SOCKETOBJECT_H
