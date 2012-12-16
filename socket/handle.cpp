
#include <socket/handle.h>
#include <sys/socket.h>
#include <iostream>

namespace archendale
{
	// SocketHandle:
	//
	handle::handle()
	{
		m_bytesSent = 0;
		m_bytesReceived = 0;
		m_socket = 0;
	} // SocketHandle

	// ~SocketHandle:
	//
	handle::~handle()
	{
		if(0 != m_socket) 
		{
			::shutdown(m_socket, SHUT_RDWR);
		} // if
	} // ~SocketHandle

	// getSocket:
	//
	int& handle::getSocket()
	{
		return m_socket;
	} // getSocket

	// ~SocketHandle:
	//
	void handle::setSocket(int socket)
	{
		m_bytesSent = 0;
		m_bytesReceived = 0;
		m_socket = socket;
	} // setSocket
} // namespace archendale
