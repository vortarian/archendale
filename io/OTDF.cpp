
#include <iostream>
#include <stdexcept>
#include <io/OTDF.h>
#include <io/IOException.h>

using namespace std;

namespace archendale
{
	OTDF::OTDF(ostream& output) : m_outputStream(output)
	{
	} // OTDF

	OTDF::OTDF(const OTDF& otdf) : m_outputStream(otdf.m_outputStream)
	{
	} // OTDF

	OTDF::~OTDF()
	{
	} // OTDF

	OTDF& OTDF::operator<<(const size_t& input)
	{
		m_outputStream << input << "\t";
		return *this;
	} // OTDF

	OTDF& OTDF::operator<<(const int& input)
	{
		m_outputStream << input << "\t";
		return *this;
	} // OTDF

	OTDF& OTDF::operator<<(const double& input)
	{
		m_outputStream << input << "\t";
		return *this;
	} // OTDF

	// Assumes for now that \t can not actually be in the file for
	// reasons other than the delimiter
	// TODO: update so that \t can appear in file
	// TODO: update algorithm so that any delimiter can be used
	OTDF& OTDF::operator<<(const string& input)
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
