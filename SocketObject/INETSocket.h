
#ifndef INETSocket_H
#define INETSocket_H

#include <SocketObject/SocketObject.h>

namespace archendale
{
	class INETSocket : public SocketObject
	{
	public:
		// INETSocket:
		//
		INETSocket();

		// ~INETSocket:
		//
		~INETSocket();
		
		// connect:
		//	Connects the current socket
		void connect();

	private:
		
	}; // INETSocket

} // namespace archendale

#endif // INETSocket_H
