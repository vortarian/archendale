
#ifndef InetAddress_H
#define InetAddress_H

#include <netdb.h>
#include <sys/types.h>
#include <string>
#include <vector>

using std::string;

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

		// getAddressLength:
		//	Return the integer length of the address
		virtual int getAddressLength() const;

		// getAddresses:
		//      returns a vector of the addresses
		virtual vector < string > getAddresses() const;

		// getAddress:
		//      returns the address of the official host
		virtual string getAddress() const;

		// getHostNames:
		//      returns a vector of strings with the Host Names, 
		//      the first name is the official name of the host
		//      subsequent names are the aliases
		virtual vector < string > getHostNames() const;

		// getHostName:
		//      returns official name of the host
		virtual string getHostName() const;

		// addAddress:
		//	returns a string of the Address	
		virtual void addAddress(const string&);

		// addHostName:
		//	returns a string of the Address	
		virtual void addHostName(const string&);
	protected:
		
		// InetAddress:
		//	Protected constructor to keep
		// 	direct instantiation from happening	
		INetworkAddress(int, int);
		
		// InetAddress:
		//	Protected constructor to keep
		// 	direct instantiation from happening	
		INetworkAddress(const INetworkAddress&);

	private:
		int 			m_addressType;
		int 			m_addressLength;
		vector < string >	m_addresses;
		vector < string > 	m_hosts;
	}; // INetworkAddress
} // namespace archendale

#endif // InetAddress_H
