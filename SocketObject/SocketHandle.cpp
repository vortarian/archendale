
#include <SocketObject/SocketHandle.h>
#include <sys/socket.h>
#include <iostream>

namespace archendale
{
	// SocketHandle:
	//
	SocketHandle::SocketHandle()
	{
		m_referenceCount++;
		m_socket = 0;
	} // SocketHandle

	// ~SocketHandle:
	//
	SocketHandle::~SocketHandle()
	{
		m_referenceCount--;
		if(0 == m_referenceCount)
		{
			std::cerr << "Shutting down socket: " << m_socket << std::endl;
			if(0 != m_socket) ::shutdown(m_socket, SHUT_RDWR);
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
		m_socket = socket;
	} // setSocket

	// increment:
	//
	void SocketHandle::increment()
	{
		m_referenceCount++;
	} // increment

	// decrement:
	//
	int SocketHandle::decrement()
	{
		m_referenceCount--;
		return m_referenceCount;
	} // getReference
} // namespace archendale
