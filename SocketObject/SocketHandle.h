
#ifndef SocketHandle_H
#define SocketHandle_H

namespace archendale
{
	class SocketHandle 
	{
	public:
		// Only want this to be used by the Socket Object

		// SocketHandle:
		//
		SocketHandle();

		// ~SocketHandle:
		//
		~SocketHandle();

		// getSocket:
		//
		int& getSocket();

		// setSocket:
		//
		void setSocket(int);

	private:
		// SocketHandle:
		//	Don't let SocketHandle's be copied
		SocketHandle(const SocketHandle&) { ; }

		int m_socket;
	}; // SocketHandle
} // namespace archendale

#endif // SocketHandle_H
