
#ifndef InternetAddress_H
#define InternetAddress_H

#include <socket/inetwork_address.h>

namespace archendale
{
	class internet_address : public network_address
	{
	public:
		// InternetAddress:
		//
		internet_address();

		// InternetAddress:
		//
		internet_address(const internet_address&);

		// ~InternetAddress:
		//
		~internet_address();
	}; // InternetAddress
} // namespace archendale

#endif // InternetAddress_H
