
#include <SocketObject/INETSocket.h>
#include <SocketObject/InternetAddress.h>
#include <SocketObject/NameResolver.h>
#include <string.h>
#include <String/String.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
                                    
namespace archendale
{
	// INETSocket:
	//
	INETSocket::INETSocket()
	{
		m_socket = socket(PF_INET, SOCK_STREAM, 6);
		if(-1 == m_socket)
		{
			cerr << "Unknown erro trying to create socket" << endl;
		} // if 
	} // INETSocket

	// ~INETSocket:
	//
	INETSocket::~INETSocket()
	{
		shutdown(m_socket, 2);
	} // ~INETSocket

	// connect:
	//	Connects the current socket
	void INETSocket::connect()
	{
		String host = "192.168.1.40";
		sockaddr_in socketAttribute;
		socketAttribute.sin_family = AF_INET;
		socketAttribute.sin_port  = htons(7);
		cerr << "Port: " << ntohs(socketAttribute.sin_port) << endl;
		cerr << "Connect: " << host.data() << endl;
		inet_aton(host.data(), &socketAttribute.sin_addr);
		if(::connect(m_socket, (sockaddr*) &socketAttribute, sizeof(socketAttribute)))
		{	
			cerr << "connect caused an error: " << errno << endl;
		} 
	} // connect
		

} // namespace archendale
