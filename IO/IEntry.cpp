
#include <IO/IEntry.h>
#include <typeinfo>

namespace archendale
{
	IEntry::IEntry(int id) : m_id(id) { ; }
	IEntry::IEntry(const IEntry& rhs) 
	{ 
		m_id = rhs.m_id;
	} // IEntry

	IEntry::~IEntry() { ; }

	const IEntry& IEntry::operator=(const IEntry& rhs) 
	{ 
		m_id = rhs.m_id;
		return *this;
	} // IEntry

	bool IEntry::operator==(const IEntry& rhs) const
	{
		if( m_id == rhs.m_id && typeid(*this) == typeid(rhs) )
			return true;
		else 
			return false;
	} // operator==

	OTDF& operator<<(OTDF& ostr, const IEntry& data)
	{
		ostr << data.m_id;
		return data.writeData(ostr);
	} // operator<<

	ITDF& operator>>(ITDF& istr, IEntry& data)
	{
		istr >> data.m_id;
		return data.readData(istr);
	} // operator>>
} // archendale
