
#ifndef OTDF_h
#define OTDF_h

#include <string>
#include <ostream>

using std::string;
using std::ostream;

namespace archendale 
{

	class OTDF
	{
	public:
		OTDF(ostream&);
		OTDF(const OTDF&);
		virtual ~OTDF();

		OTDF& operator<<(const double&);
		OTDF& operator<<(const string&);
	private:
		ostream& m_outputStream;
	}; // OTDF

} // archendale

#endif // OTDF
