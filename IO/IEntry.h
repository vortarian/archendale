
#ifndef IEntry_h
#define IEntry_h

#include <iostream>

namespace archendale 
{
	/*
	 * Base class to be used for dynamically reading & writing data to the various IO 
	 * utilities, like OTDF & ITDF
	 *
	 * A consumer is expected to implement wirteData & readData to fill a contract
	 * to read it's data in & out.
	 */
	class IEntry 
	{
	public:
		IEntry();
		IEntry(const IEntry&);
		virtual ~IEntry() = 0;
		
		virtual ostream& writeData(ostream&) const = 0;
		virtual istream& readData(istream&) = 0;
	}; // IEntry

	ostream& operator<<(ostream& ostr, const IEntry& data)
	{
		return data.writeData(ostr);
	} // operator<<

	istream& operator>>(istream& istr, IEntry& data)
	{
		return data.readData(istr);
	} // operator>>
} // namespace

#endif // IEntry_h
