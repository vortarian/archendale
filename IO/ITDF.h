
#ifndef ITDF_h
#define ITDF_h

#include <string>
#include <istream>

namespace archendale 
{

	class ITDF
	{
	public:
		ITDF(std::istream&);
		ITDF(const ITDF&);
		virtual ~ITDF();

		ITDF& operator>>(int&);
		ITDF& operator>>(double&);
		ITDF& operator>>(std::string&);
	private:
		std::istream& m_inputStream;
	}; // ITDF

} // archendale

#endif // ITDF
