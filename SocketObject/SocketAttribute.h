
#ifndef SOCKETATTRIBUTE_H
#define SOCKETATTRIBUTE_H

#include <sys/types.h>
#include <sys/socket.h>    
#include <String/String.h>    

namespace archendale
{
	class SocketAttribute 
	{
	public:
		// SocketAttribute Constructores:
		//	Constructer for a Socket Attribute
		//	Format:
		//	SocketAttribute(hoststring /* "host:port" */)
		//	SocketAttribute(port, host)
		//	SocketAttribute(portName, host)
		//
		SocketAttribute(unsigned int, String = "localhost");
		SocketAttribute(String, String = "localhost");
		virtual ~SocketAttribute();

		// setHostName:
		//	sets the host name that the socket listens on
		void setHostName();

		// setPort
		//	sets the port the host will listen on
		void setPort(unsigned int);
		void setPort(String);
	private:
		String m_hostName;
		unsigned int m_portNumber;
	}; // SocketAttribute
}; // archendale

#endif // SOCKETATTRIBUTE_H

