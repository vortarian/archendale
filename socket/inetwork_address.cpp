#include <socket/inetwork_address.h>
#include <string>
#include <string.h>

using std::string;

namespace archendale
{
	// TODO:
	//	Need to add support for Network Byte Order
	
	//	Protected constructor to keep
	// 	direct instantiation from happening	
	network_address::network_address(int addrType, int addrLength)
	{ 
		m_addressType = addrType;
		m_addressLength = addrLength;
	} // INetworkAddress

	network_address::network_address(const network_address& addr)
	{ 
		m_addressType 	= addr.m_addressType;
		m_addressLength = addr.m_addressLength;
		m_addresses 	= addr.m_addresses;
		m_hosts 	= addr.m_hosts;
	} // INetworkAddress

	// ~INetworkAddress:
	//
	network_address::~network_address()
	{
	} // INetworkAddress

	// getType:
	//	Return the integer type of the address
	int network_address::getType() const
	{
		return m_addressType;
	} // getType

	// getAddressLength:
	//	Return the integer type of the address
	int network_address::getAddressLength() const
	{
		return m_addressLength;
	} // getAddressLength

	// getAddresses:
	//	returns a vector of the addresses
	vector < string > network_address::getAddresses() const
	{
		return m_addresses;
	} // getAddress

	// getAddress:
	//	returns the address of the official host
	string network_address::getAddress() const
	{
		string address;
		vector < string >::const_iterator beg = m_addresses.begin();
		vector < string >::const_iterator end = m_addresses.end();
		if(beg != end) address = *beg;
		return address;
	} // getAddress

	// getHostNames:
	//	returns a vector of strings with the Host Names, 
	//	the first name is the official name of the host
	//	subsequent names are the aliases
	vector < string > network_address::getHostNames() const
	{
		return m_hosts;
	} // getHostNames

	// getHostName:
	//	returns the official name of the host
	string network_address::getHostName() const
	{
		string host;
		vector < string >::const_iterator beg = m_hosts.begin();
		vector < string >::const_iterator end = m_hosts.end();
		if(beg != end) host = *beg;
		return host;
	} // getHostNames

	// addAddress:
	//      adds a string of the Address
	void network_address::addAddress(const string& addr)
	{
		m_addresses.push_back(addr);
	} // addAddress

	// addHostName:
	//      adds a string of the host
	void network_address::addHostName(const string& host)
	{
		m_hosts.push_back(host);
	} // addHostName

} // namespace archendale
