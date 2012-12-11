#include <socket/InternetAddress.h>
#include <sys/types.h>

namespace archendale
{
	// InternetAddress:
	//
	InternetAddress::InternetAddress() : INetworkAddress(PF_INET, 4)
	{
	} // InternetAddress

	// InternetAddress:
	//
	InternetAddress::InternetAddress(const InternetAddress& addr) : INetworkAddress(addr)
	{
	} // InternetAddress

	// ~InternetAddress:
	//
	InternetAddress::~InternetAddress()
	{
	} // ~InternetAddress

} // namespace archendale
