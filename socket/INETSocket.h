
#ifndef INETSocket_H
#define INETSocket_H

#include <socket/SocketObject.h>
#include <socket/InternetAddress.h>

namespace archendale
{
	class INETSocket : public SocketObject
	{
		friend class SocketServer;
	public:
		// INETSocket:
		// 	Default constructor to use for SocketServer
		INETSocket();

		// INETSocket:
		//
		INETSocket(const InternetAddress&, int);

		// INETSocket:
		//
		INETSocket(const INETSocket&);

		// ~INETSocket:
		//
		~INETSocket();

		// operator=
		//
		const INETSocket& operator=(const INETSocket&);

		// connect:
		//	Connects the current socket
		void connect();

		// setAddress
		// 	Set the address of this socket
		void setAddress(const InternetAddress&);
		
		// setPort
		//	Set the port of this socket
		void setPort(int port);
	private:
		InternetAddress m_address;	
		unsigned int m_port;
		const string m_protocolName;
	}; // INETSocket

} // namespace archendale

#endif // INETSocket_H
