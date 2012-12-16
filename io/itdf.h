
#ifndef ITDF_h
#define ITDF_h

#include <string>
#include <istream>

namespace archendale 
{

	class itdf
	{
	public:
		itdf(std::istream&);
		itdf(const itdf&);
		virtual ~itdf();

		itdf& operator>>(size_t&);
		itdf& operator>>(int&);
		itdf& operator>>(double&);
		itdf& operator>>(std::string&);
	private:
		std::istream& m_inputStream;
	}; // ITDF

} // archendale

#endif // ITDF
