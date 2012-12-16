
#ifndef IEntry_h
#define IEntry_h

#include <io/itdf.h>
#include <io/otdf.h>

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
	class ientry 
	{
	friend otdf& operator<<(otdf&, const ientry&);
	friend itdf& operator>>(itdf&, ientry&);

	public:
		ientry(int = 0);
		ientry(const ientry&);
		virtual ~ientry();
		
		virtual otdf& writeData(otdf&) const = 0;
		virtual itdf& readData(itdf&) = 0;
		virtual const std::string& getName() = 0;

		virtual const ientry& operator=(const ientry&);
		virtual bool operator==(const ientry&) const;
	protected:
		int m_id;
	}; // IEntry

	otdf& operator<<(otdf&, const ientry&);
	itdf& operator>>(itdf&, ientry&);

} // namespace

#endif // IEntry_h
