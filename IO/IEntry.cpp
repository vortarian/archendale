
#include <IEntry.h>

namespace archendale
{
	OTDF& operator<<(OTDF& ostr, const IEntry& data)
	{
		return data.writeData(ostr);
	} // operator<<

	ITDF& operator>>(ITDF& istr, IEntry& data)
	{
		return data.readData(istr);
	} // operator>>
} // archendale
