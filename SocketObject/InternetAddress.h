
#ifndef InternetAddress_H
#define InternetAddress_H

#include <SocketObject/INetworkAddress.h>

namespace archendale
{
	class InternetAddress : public INetworkAddress
	{
	public:
		// InternetAddress:
		//
		InternetAddress();

		// ~InternetAddress:
		//
		~InternetAddress();
	}; // InternetAddress
} // namespace archendale

#endif // InternetAddress_H