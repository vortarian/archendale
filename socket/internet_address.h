
#ifndef InternetAddress_H
#define InternetAddress_H

#include <socket/inetwork_address.h>

namespace archendale
{
	class InternetAddress : public INetworkAddress
	{
	public:
		// InternetAddress:
		//
		InternetAddress();

		// InternetAddress:
		//
		InternetAddress(const InternetAddress&);

		// ~InternetAddress:
		//
		~InternetAddress();
	}; // InternetAddress
} // namespace archendale

#endif // InternetAddress_H
