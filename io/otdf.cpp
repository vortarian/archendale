
#include <iostream>
#include <stdexcept>
#include <io/otdf.h>
#include <io/exception.h>

using namespace std;

namespace archendale
{
	otdf::otdf(ostream& output) : m_outputStream(output)
	{
	} // OTDF

	otdf::otdf(const otdf& otdf) : m_outputStream(otdf.m_outputStream)
	{
	} // OTDF

	otdf::~otdf()
	{
	} // OTDF

	otdf& otdf::operator<<(const size_t& input)
	{
		m_outputStream << input << "\t";
		return *this;
	} // OTDF

	otdf& otdf::operator<<(const int& input)
	{
		m_outputStream << input << "\t";
		return *this;
	} // OTDF

	otdf& otdf::operator<<(const double& input)
	{
		m_outputStream << input << "\t";
		return *this;
	} // OTDF

	// Assumes for now that \t can not actually be in the file for
	// reasons other than the delimiter
	// TODO: update so that \t can appear in file
	// TODO: update algorithm so that any delimiter can be used
	otdf& otdf::operator<<(const string& input)
	{
                string replaceText(8, ' ');
                unsigned int startIndex = 0;
		string modifiableInput = input;

                try
                {
                        while(string::npos != (startIndex = modifiableInput.find('\t', startIndex)))
                        {
                                modifiableInput.replace(startIndex, 1, replaceText);
                        } // while
                } catch(out_of_range)
                {
                        // They are all replaced if we get here
                } // try

		m_outputStream << modifiableInput << "\t";
		return *this;
	} // OTDF
	
} // archendale
