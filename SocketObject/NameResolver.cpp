
#include <SocketObject/NameResolver.h>
#include <SocketObject/SocketException.h>

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
	NameResolver::NameResolver()
	{
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
	InternetAddress NameResolver::getAddress(const InternetAddress addr)
	{
		struct hostent* hostinfo;
		hostinfo = gethostbyname(addr.getHostName().data());
		cerr << hostinfo << endl;
		if(!hostinfo) 
		{
			switch(h_errno)
			{
				case HOST_NOT_FOUND:
					{
						UnknownHostException uhexp(addr.getHostName());
						throw uhexp;
					}
					break;
				case TRY_AGAIN:
					{
						RetryHostLookupException rhle(addr.getHostName());
						throw rhle;
					}
					break;
				case NO_DATA:
					{
						HostWithNoAddressException hwnae(addr.getHostName());
						throw hwnae;
					}
					break;
				default:
					Exception exp(addr.getHostName() + ": Unknown error occured");
					throw exp;
					break;
			} // switch
		} // if
		return populateAddress(hostinfo);
	} // getAddress

	// getName:
	//      returns the IP Address of a given name
	//      takes a string arguement which is the
	//      server to be looked up 
	InternetAddress NameResolver::getName(const InternetAddress addr)
	{
		struct hostent* hostinfo = gethostbyaddr(addr.getAddress().data(), addr.getAddressLength(), addr.getType());
		if(!hostinfo) 
		{
			switch(h_errno)
			{
				case HOST_NOT_FOUND:
					{
						UnknownHostException uhexp(addr.getAddress());
						throw uhexp;
					}
					break;
				case TRY_AGAIN:
					{
						RetryHostLookupException rhle(addr.getAddress());
						throw rhle;
					}
					break;
				case NO_DATA:
					{
						HostWithNoAddressException hwnae(addr.getAddress());
						throw hwnae;
					}
					break;
				default:
					Exception exp(addr.getAddress() + ": Unknown error occured");
					throw exp;
					break;
			} // switch
		} // if
		return populateAddress(hostinfo);
	} // getName

	// populateAddress:
	//
	InternetAddress NameResolver::populateAddress(hostent* hostinfo)
	{
		InternetAddress address;
		address.addHostName(hostinfo->h_name);
		for(int i = 0; hostinfo->h_aliases[i]; i++)
		{
			address.addHostName(hostinfo->h_aliases[i]);
		} // for

		for(int i = 0; hostinfo->h_addr_list[i]; i++)
		{
			cerr << "Adding address: " << hostinfo->h_addr_list[i] << endl;
			address.addAddress(hostinfo->h_addr_list[i]);
			i++;
		} // for
		endhostent();
		return address;
	} // getName
	
} // namespace archendale
