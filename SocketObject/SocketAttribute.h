
#ifndef SOCKETATTRIBUTE_H
#define SOCKETATTRIBUTE_H

#include <sys/types.h>
#include <sys/socket.h>    
#include <string>    

using std::string;

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
		SocketAttribute(unsigned int, string = "localhost");
		SocketAttribute(string, string = "localhost");
		virtual ~SocketAttribute();

		// setHostName:
		//	sets the host name that the socket listens on
		void setHostName();

		// setPort
		//	sets the port the host will listen on
		void setPort(unsigned int);
		void setPort(string);
	private:
		string m_hostName;
		unsigned int m_portNumber;
	}; // SocketAttribute
}; // archendale

#endif // SOCKETATTRIBUTE_H

