#include <SocketObject/InternetAddress.h>
#include <sys/types.h>

namespace archendale
{
	// InternetAddress:
	//
	InternetAddress::InternetAddress() : INetworkAddress(PF_INET)
	{
	} // InternetAddress

	// ~InternetAddress:
	//
	InternetAddress::~InternetAddress()
	{
	} // ~InternetAddress

} // namespace archendale
