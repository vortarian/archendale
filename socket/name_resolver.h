
#ifndef NameResolver_H
#define NameResolver_H

#include <netdb.h>
#include <vector>
#include <thread/mutex.h>
#include <socket/internet_address.h>

using std::vector;

namespace archendale
{
	class name_resolver
	{
	public:
		// NameResolver:
		name_resolver();

		// ~NameResolver:
		~name_resolver();

		// getAddress:
		//	returns the IP Address of a given name	
		//	takes a string arguement which is the 
		//	server to be looked up
		static internet_address getAddress(const string&);

	private:
		static internet_address populateAddress(hostent*);
		static mutex mut; // BSD Functions are not reentrant, must mutex them
	}; // NameResolver
}; // namespace archendale

#endif // NameResolver_H
