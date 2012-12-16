#include <socket/internet_address.h>
#include <sys/types.h>

namespace archendale
{
	// InternetAddress:
	//
	internet_address::internet_address() : network_address(PF_INET, 4)
	{
	} // InternetAddress

	// InternetAddress:
	//
	internet_address::internet_address(const internet_address& addr) : network_address(addr)
	{
	} // InternetAddress

	// ~InternetAddress:
	//
	internet_address::~internet_address()
	{
	} // ~InternetAddress

} // namespace archendale
