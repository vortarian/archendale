
#ifndef NameResolver_H
#define NameResolver_H

#include <netdb.h>
#include <vector>
#include <ThreadObject/Mutex.h>
#include <ThreadObject/AutoMutex.h>
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
		static InternetAddress getAddress(const string&);

	private:
		static InternetAddress populateAddress(hostent*);
		static Mutex mut; // BSD Functions are not reentrant, must mutex them
	}; // NameResolver
}; // namespace archendale

#endif // NameResolver_H
