
#ifndef SocketServer_H
#define SocketServer_H

#include <socket/socket.h>
#include <socket/internet_address.h>
#include <socket/inet.h>
#include <thread/mutex.h>

namespace archendale
{
	class server : public socket
	{
	public:
		// SocketServer:
		//
		server(const internet_address&, int, int = 10);

		// ~SocketServer:
		//
		virtual ~server();

		// isWaiting:
		//	RET number of waiting connections if there is a connection waiting
		int isWaiting();

		// getSocket:
		//	Returns a connected socket
		inet getWaitingConnection();

	private:
		// SocketServer:
		//	Don't want any copying going on here
		server(const server&) { ; }

		// bind:
		//
		void bind();
		
		// listen:
		// 
		void listen();
	
		internet_address m_address;	
		int m_port;
		int m_backlog; // The number of connections to be allowed to wait at a time
		const string m_protocolName;
		mutex m_serverMutex;
	}; // SocketServer
} // namespace archendale

#endif // SocketServer_H
