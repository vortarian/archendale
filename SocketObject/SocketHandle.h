
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

		// increment:
		//
		void increment();	
			
		// decrement:
		//
		int decrement();	
			
		// getSocket:
		//
		int& getSocket();

		// setSocket:
		//
		void setSocket(int);

	private:
		// SocketHandle:
		//
		SocketHandle(const SocketHandle&) { ; }

		unsigned int m_referenceCount; 
		int m_socket;
	}; // SocketHandle
} // namespace archendale

#endif // SocketHandle_H
