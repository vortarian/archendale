#include <IO/OTDF.h>
#include <IO/IOException.h>
#include <iostream>

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
		m_outputStream << input << "\t";
		return *this;
	} // OTDF
	
} // archendale
