
#ifndef NameResolver_H
#define NameResolver_H

#include <netdb.h>
#include <vector>
#include <String/String.h>
#include <SocketObject/InternetAddress.h>

using std::vector;

namespace archendale
{
	class NameResolver
	{
	public:
		// NameResolver:
		NameResolver();

		// ~NameResolver:
		~NameResolver();

		// getAddress:
		//	returns the IP Address of a given name	
		//	takes a string arguement which is the 
		//	server to be looked up
		static InternetAddress getAddress(const InternetAddress);

		// getName:
		//	returns the IP Address of a given name	
		//	takes a string arguement which is the 
		//	server to be looked up
		//	The first Name in the Iterator is the
		//	official name of the host, all subsequent names
		//	are alias's
		static InternetAddress getName(const InternetAddress);

	private:
		static InternetAddress populateAddress(hostent*);
	}; // NameResolver
}; // namespace archendale

#endif // NameResolver_H
