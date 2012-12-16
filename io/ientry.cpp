
#include <io/ientry.h>
#include <typeinfo>

namespace archendale
{
	ientry::ientry(int id) : m_id(id) { ; }
	ientry::ientry(const ientry& rhs) 
	{ 
		m_id = rhs.m_id;
	} // IEntry

	ientry::~ientry() { ; }

	const ientry& ientry::operator=(const ientry& rhs) 
	{ 
		m_id = rhs.m_id;
		return *this;
	} // IEntry

	bool ientry::operator==(const ientry& rhs) const
	{
		if( m_id == rhs.m_id && typeid(*this) == typeid(rhs) )
			return true;
		else 
			return false;
	} // operator==

	otdf& operator<<(otdf& ostr, const ientry& data)
	{
		ostr << data.m_id;
		return data.writeData(ostr);
	} // operator<<

	itdf& operator>>(itdf& istr, ientry& data)
	{
		istr >> data.m_id;
		return data.readData(istr);
	} // operator>>
} // archendale
