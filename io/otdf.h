
#ifndef OTDF_h
#define OTDF_h

#include <string>
#include <ostream>

namespace archendale 
{

	class otdf
	{
	public:
		otdf(std::ostream&);
		otdf(const otdf&);
		virtual ~otdf();

		otdf& operator<<(const size_t&);
		otdf& operator<<(const int&);
		otdf& operator<<(const double&);
		otdf& operator<<(const std::string&);
	private:
		std::ostream& m_outputStream;
	}; // OTDF

} // archendale

#endif // OTDF
