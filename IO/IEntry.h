
#ifndef IEntry_h
#define IEntry_h

#include <IO/ITDF.h>
#include <IO/OTDF.h>

namespace archendale 
{
	/*
	 * Base class to be used for dynamically reading & writing data to the various IO 
	 * utilities, like OTDF & ITDF
	 *
	 * A consumer is expected to implement writeData & readData to fill a contract
	 * to read it's data in & out.
	 */
	class IEntry 
	{
	public:
		IEntry() { ; }
		IEntry(const IEntry&) { ; }
		virtual ~IEntry() { ; }
		
		virtual OTDF& writeData(OTDF&) const = 0;
		virtual ITDF& readData(ITDF&) = 0;
		virtual const std::string& getName() = 0;
	}; // IEntry

	OTDF& operator<<(OTDF& ostr, const IEntry& data);
	ITDF& operator>>(ITDF& istr, IEntry& data);

} // namespace

#endif // IEntry_h
