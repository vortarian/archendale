
#include <socket/NameResolver.h>
#include <socket/SocketException.h>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread/Mutex.h>


namespace archendale
{
	// Implementation class	
	// TODO: verfiy that this works on BigEndian & LittleEndian Systems
	union dataconverter 
	{
		char cdata[16];
		unsigned int idata;
		long ldata;
	}; // union

	Mutex NameResolver::mut;

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
	InternetAddress NameResolver::getAddress(const string& hostName)
	{
		AutoMutex aMutex(mut);
		struct hostent* hostinfo;
		hostinfo = gethostbyname(hostName.c_str());
		if(!hostinfo) 
		{
			switch(h_errno)
			{
				case HOST_NOT_FOUND:
					{
						UnknownHostException uhexp(hostName);
						throw uhexp;
					}
					break;
				case TRY_AGAIN:
					{
						RetryHostLookupException rhle(hostName);
						throw rhle;
					}
					break;
				case NO_DATA:
					{
						HostWithNoAddressException hwnae(hostName);
						throw hwnae;
					}
					break;
				default:
					SocketException exp(hostName + ": Unknown error occured");
					throw exp;
					break;
			} // switch
		} // if
		return populateAddress(hostinfo);
	} // getAddress

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

		dataconverter charToInteger;
		in_addr internetIPNetworkByteOrder;
		string readableAddress;
		for(int i = 0; hostinfo->h_addr_list[i]; i++)
		{
			// Should theoretically work for 128 bit and 32 bit addresses . . .
			for(int j = 0; j < hostinfo->h_length; j++) 
			{
				charToInteger.cdata[j] = hostinfo->h_addr_list[i][j];
			} // for
			if(4 == hostinfo->h_length) 
			{
				internetIPNetworkByteOrder.s_addr = charToInteger.idata;
			} else if(16 == hostinfo->h_length) {
				internetIPNetworkByteOrder.s_addr = charToInteger.ldata;
			} // if
			readableAddress = inet_ntoa(internetIPNetworkByteOrder);
			address.addAddress(readableAddress);
		} // for
		return address;
	} // getName

} // namespace archendale
