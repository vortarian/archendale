
#include <SocketObject/INetworkAddress.h>
#include <String/String.h>
#include <string.h>

namespace archendale
{
	// TODO:
	//	Need to add support for Network Byte Order
	
	//	Protected constructor to keep
	// 	direct instantiation from happening	
	INetworkAddress::INetworkAddress(int addrType) : m_addressType(addrType) 
	{
	} // INetworkAddress

	// ~INetworkAddress:
	//
	INetworkAddress::~INetworkAddress()
	{
	} // INetworkAddress

	// getType:
	//	Return the integer type of the address
	int INetworkAddress::getType() const
	{
		return m_addressType;
	} // getType

	// getAddresses:
	//	returns a vector of the addresses
	vector < String > INetworkAddress::getAddresses() const
	{
		return m_addresses;
	} // getAddress

	// getAddress:
	//	returns the address of the official host
	String INetworkAddress::getAddress() const
	{
		String address;
		vector < String >::const_iterator beg = m_addresses.begin();
		vector < String >::const_iterator end = m_addresses.end();
		if(++beg != end) address = *beg;
		return address;
	} // getAddress

	// getHostNames:
	//	returns a vector of strings with the Host Names, 
	//	the first name is the official name of the host
	//	subsequent names are the aliases
	vector < String > INetworkAddress::getHostNames() const
	{
		return m_hosts;
	} // getHostNames

	// getHostNam:
	//	returns the official name of the host
	String INetworkAddress::getHostName() const
	{
		String host;
		vector < String >::const_iterator beg = m_hosts.begin();
		vector < String >::const_iterator end = m_hosts.end();
		if(++beg != end) host = *beg;
		return host;
	} // getHostNames

	// addAddress:
	//      returns a String of the Address
	void INetworkAddress::addAddress(const String& addr)
	{
		m_addresses.push_back(addr);
	} // addAddress

	// addHostName:
	//      returns a String of the Address
	void INetworkAddress::addHostName(const String& host)
	{
		m_hosts.push_back(host);
	} // addHostName

} // namespace archendale
