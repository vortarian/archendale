
#ifndef InetAddress_H
#define InetAddress_H

#include <netdb.h>
#include <sys/types.h>
#include <String/String.h>
#include <vector>

namespace archendale
{
	using std::vector;

	class INetworkAddress 
	{
	public:

		// ~InetAddress:
		//
		virtual ~INetworkAddress();

		// getType:
		//	Return the integer type of the address
		virtual int getType() const;

		// getAddresses:
		//      returns a vector of the addresses
		virtual vector < String > getAddresses() const;

		// getAddress:
		//      returns the address of the official host
		virtual String getAddress() const;

		// getHostNames:
		//      returns a vector of strings with the Host Names, 
		//      the first name is the official name of the host
		//      subsequent names are the aliases
		virtual vector < String > getHostNames() const;

		// getHostName:
		//      returns official name of the host
		virtual String getHostName() const;

		// addAddress:
		//	returns a String of the Address	
		virtual void addAddress(const String&);

		// addHostName:
		//	returns a String of the Address	
		virtual void addHostName(const String&);

	protected:
		
		// InetAddress:
		//	Protected constructor to keep
		// 	direct instantiation from happening	
		INetworkAddress(int);

	private:
		const int 		m_addressType;
		vector < String >	m_addresses;
		vector < String > 	m_hosts;
	}; // INetworkAddress
} // namespace archendale

#endif // InetAddress_H
