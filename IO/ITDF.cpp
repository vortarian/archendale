#include <IO/ITDF.h>
#include <IO/IOException.h>
#include <iostream>
using namespace std;
namespace archendale
{

	// helper funciton
	// plagerised from Strostoup, 21.3.4
	istream& eatwhite(istream& is)
	{
		char c;
		while(is.get(c))
		{
			if(!isspace(c))
			{
				is.putback(c);
				break;
			} // if
		} // while
		return is;
	} // eatwhite

	ITDF::ITDF(istream& input) : m_inputStream(input)
	{
	} // ITDF

	ITDF::ITDF(const ITDF& itdf) : m_inputStream(itdf.m_inputStream)
	{
	} // ITDF

	ITDF::~ITDF()
	{
	} // ITDF


	ITDF& ITDF::operator>>(double& out)
	{
		eatwhite(m_inputStream);
		if(!m_inputStream.eof() && m_inputStream.good())
		{
			m_inputStream >> out;
		} else
		{
			EOFException exp("End of file reached");
			throw exp;
		} // if
		return *this;
	} // ITDF


	ITDF& ITDF::operator>>(int& out)
	{
		eatwhite(m_inputStream);
		if(!m_inputStream.eof() && m_inputStream.good())
		{
			m_inputStream >> out;
		} else
		{
			EOFException exp("End of file reached");
			throw exp;
		} // if
		return *this;
	} // ITDF

	// Assumes for now that \t can not actually be in the file for
	// reasons other than the delimiter
	// TODO: update so that \t can appear in file
	// TODO: update algorithm so that any delimiter can be used
	ITDF& ITDF::operator>>(string& out)
	{
		string buffer;
		out = "";
		if(!m_inputStream.eof() && m_inputStream.good())
		{
			getline(m_inputStream, out, '\t');
			if(!m_inputStream.good())
			{
				EOFException exp("End of file reached");
				throw exp;
			} // if
			getline(m_inputStream, out, '\t');
		} else 
		{
				EOFException exp("End of file reached");
				throw exp;
		} // if
		return *this;
	} // ITDF
	
} // archendale
