
#ifndef OTDF_h
#define OTDF_h

#include <string>
#include <ostream>

namespace archendale 
{

	class OTDF
	{
	public:
		OTDF(std::ostream&);
		OTDF(const OTDF&);
		virtual ~OTDF();

		OTDF& operator<<(const int&);
		OTDF& operator<<(const double&);
		OTDF& operator<<(const std::string&);
	private:
		std::ostream& m_outputStream;
	}; // OTDF

} // archendale

#endif // OTDF
