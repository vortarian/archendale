
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
	 * 
	 * It is highly suggested that the user take a look at the default 
	 * operator== and decide if they want to use it, as well as setting
	 * the m_id variable via the constructor to be a unique number
	 */
	class IEntry 
	{
	friend OTDF& operator<<(OTDF&, const IEntry&);
	friend ITDF& operator>>(ITDF&, IEntry&);

	public:
		IEntry(int = 0);
		IEntry(const IEntry&);
		virtual ~IEntry();
		
		virtual OTDF& writeData(OTDF&) const = 0;
		virtual ITDF& readData(ITDF&) = 0;
		virtual const std::string& getName() = 0;

		virtual const IEntry& operator=(const IEntry&);
		virtual bool operator==(const IEntry&) const;
	protected:
		int m_id;
	}; // IEntry

	OTDF& operator<<(OTDF&, const IEntry&);
	ITDF& operator>>(ITDF&, IEntry&);

} // namespace

#endif // IEntry_h
