
#ifndef INETSocket_H
#define INETSocket_H

#include <socket/socket.h>
#include <socket/internet_address.h>

namespace archendale
{
	class inet : public socket
	{
		friend class server;
	public:
		// INETSocket:
		// 	Default constructor to use for SocketServer
		inet();

		// INETSocket:
		//
		inet(const internet_address&, int);

		// INETSocket:
		//
		inet(const inet&);

		// ~INETSocket:
		//
		~inet();

		// operator=
		//
		const inet& operator=(const inet&);

		// connect:
		//	Connects the current socket
		void connect();

		// setAddress
		// 	Set the address of this socket
		void setAddress(const internet_address&);
		
		// setPort
		//	Set the port of this socket
		void setPort(int port);
	private:
		internet_address m_address;	
		unsigned int m_port;
		const string m_protocolName;
	}; // INETSocket

} // namespace archendale

#endif // INETSocket_H
