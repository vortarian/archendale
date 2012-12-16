
#include <socket/handle.h>
#include <sys/socket.h>
#include <iostream>

namespace archendale
{
	// SocketHandle:
	//
	SocketHandle::SocketHandle()
	{
		m_bytesSent = 0;
		m_bytesReceived = 0;
		m_socket = 0;
	} // SocketHandle

	// ~SocketHandle:
	//
	SocketHandle::~SocketHandle()
	{
		if(0 != m_socket) 
		{
			::shutdown(m_socket, SHUT_RDWR);
		} // if
	} // ~SocketHandle

	// getSocket:
	//
	int& SocketHandle::getSocket()
	{
		return m_socket;
	} // getSocket

	// ~SocketHandle:
	//
	void SocketHandle::setSocket(int socket)
	{
		m_bytesSent = 0;
		m_bytesReceived = 0;
		m_socket = socket;
	} // setSocket
} // namespace archendale
