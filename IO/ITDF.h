
#ifndef ITDF_h
#define ITDF_h

#include <string>
#include <istream>

using std::string;
using std::istream;

namespace archendale 
{

	class ITDF
	{
	public:
		ITDF(istream&);
		ITDF(const ITDF&);
		virtual ~ITDF();

		ITDF& operator>>(int&);
		ITDF& operator>>(double&);
		ITDF& operator>>(string&);
	private:
		istream& m_inputStream;
	}; // ITDF

} // archendale

#endif // ITDF
