
#ifndef SocketServer_H
#define SocketServer_H

#include <SocketObject/SocketObject.h>
#include <SocketObject/InternetAddress.h>
#include <SocketObject/INETSocket.h>
#include <ThreadObject/Mutex.h>

namespace archendale
{
	class SocketServer : public SocketObject
	{
	public:
		// SocketServer:
		//
		SocketServer(const InternetAddress&, int, int = 10);

		// ~SocketServer:
		//
		virtual ~SocketServer();

		// isWaiting:
		//	RET number of waiting connections if there is a connection waiting
		int isWaiting();

		// getSocket:
		//	Returns a connected socket
		INETSocket getWaitingConnection();

	private:
		// SocketServer:
		//	Don't want any copying going on here
		SocketServer(const SocketServer&) { ; }

		// bind:
		//
		void bind();
		
		// listen:
		// 
		void listen();
	
		InternetAddress m_address;	
		int m_port;
		int m_backlog; // The number of connections to be allowed to wait at a time
		Mutex m_serverMutex;
	}; // SocketServer
} // namespace archendale

#endif // SocketServer_H