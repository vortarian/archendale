
#ifndef SocketHandle_H
#define SocketHandle_H

namespace archendale
{
	class handle 
	{
	public:
		// Only want this to be used by the Socket Object

		// SocketHandle:
		//
		handle();

		// ~SocketHandle:
		//
		~handle();

		// getSocket:
		//
		int& getSocket();

		// setSocket:
		//
		void setSocket(int);

		// incrementBytesSent:
		//
		void incrementBytesSent(unsigned int amount) { m_bytesSent += amount; }

		// incrementBytesReceived:
		//
		void incrementBytesReceived(unsigned int amount) { m_bytesReceived += amount; }

		// getBytesSent:
		//
		unsigned int getBytesSent() { return m_bytesSent; }

		// getBytesReceived:
		//
		unsigned int getBytesReceived() { return m_bytesReceived; }
	private:
		// SocketHandle:
		//	Don't let SocketHandle's be copied
		handle(const handle&) { ; }
		
		// operator=
		//	Don't let SocketHandle's be copied
		bool operator=(const handle&) { ; }

		unsigned int m_bytesSent, m_bytesReceived;
		int m_socket;
	}; // SocketHandle
} // namespace archendale

#endif // SocketHandle_H
