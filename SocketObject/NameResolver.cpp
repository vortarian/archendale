
#include <SocketObject/NameResolver.h>
#include <Exception/Exception.h>

namespace archendale
{
	//String            m_hostName;
	//vector < String > m_aliasList;
	//int               m_addressType;
	//vector < String >    m_addressList;

	// TODO:
	//	Need to define & add exceptions for all these classes

	// NameResolver:
	//	Builds from a hostName
	NameResolver::NameResolver(const String& hostName)
	{
		m_hostName = hostName;
		struct hostent* hostinfo = gethostbyname(hostName.data());
		m_aliasList.push_back(hostinfo->h_name);
		for(int i = 0; hostinfo->h_aliases[i]; i++)
		{
			m_aliasList.push_back(hostinfo->h_aliases[i]);
		} // for

		for(int i = 0; hostinfo->h_addr_list[i]; i++)
		{
			m_addressList.push_back(hostinfo->h_addr_list[i]);
			i++;
		} // for
	} // NameResolver

	// NameResolver:
	// 	Builds from an IP address
	//
	NameResolver::NameResolver(unsigned int)
	{
		NotImplementedException exp;
		throw exp;
	} // NameResolver

	// ~NameResolver:
	//
	NameResolver::~NameResolver()
	{
	} // ~NameResolver

	// getAddress:
	//      returns the IP Address of a given name
	//      takes a string arguement which is the
	//      server to be looked up
	vector < String > NameResolver::getAddress()
	{
		return m_addressList;
	} // getAddress

	// getName:
	//      returns the IP Address of a given name
	//      takes a string arguement which is the
	//      server to be looked up 
	//      The first Name in the Iterator is the
	//      official name of the host, all subsequent names
	//      are alias's
	vector < String > NameResolver::getName()
	{
		return m_aliasList;
	} // getName

} // namespace archendale
