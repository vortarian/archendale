
#ifndef NameResolver_H
#define NameResolver_H

#include <netdb.h>
#include <vector>
#include <String/String.h>

using std::vector;

namespace archendale
{
	class NameResolver
	{
	public:
		// NameResolver:
		//	Takes the host name and acquires information
		NameResolver(const String&);

		// NameResolver:
		//	Takes a host IP Address and acquires information
		NameResolver(unsigned int);

		// ~NameResolver:
		//
		~NameResolver();

		// getAddress:
		//	returns the IP Address of a given name	
		//	takes a string arguement which is the 
		//	server to be looked up
		vector < String > getAddress();

		// getName:
		//	returns the IP Address of a given name	
		//	takes a string arguement which is the 
		//	server to be looked up
		//	The first Name in the Iterator is the
		//	official name of the host, all subsequent names
		//	are alias's
		vector < String > getName();

	private:
		String 		  m_hostName;
		vector < String > m_aliasList;	
		int		  m_addressType;
		vector < String > m_addressList;

	}; // NameResolver
}; // namespace archendale

#endif // NameResolver_H
