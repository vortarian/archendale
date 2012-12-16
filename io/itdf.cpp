#include <io/itdf.h>
#include <io/exception.h>
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

	itdf::itdf(istream& input) : m_inputStream(input)
	{
	} // ITDF

	itdf::itdf(const itdf& itdf) : m_inputStream(itdf.m_inputStream)
	{
	} // ITDF

	itdf::~itdf()
	{
	} // ITDF

	itdf& itdf::operator>>(double& out)
	{
		eatwhite(m_inputStream);
		if(!m_inputStream.eof() && m_inputStream.good())
		{
			m_inputStream >> out;
			// remove trailing tab if it exists
			char c;
			m_inputStream.get(c);
			if(c != '\t')
			{
				m_inputStream.putback(c);
			} // if
		} else
		{
			EOFException exp("End of file reached");
			throw exp;
		} // if
		return *this;
	} // ITDF

	itdf& itdf::operator>>(size_t& out)
	{
		eatwhite(m_inputStream);
		if(!m_inputStream.eof() && m_inputStream.good())
		{
			m_inputStream >> out;

			// remove trailing tab if it exists
			char c;
			m_inputStream.get(c);
			if(c != '\t')
			{
				m_inputStream.putback(c);
			} // if
		} else
		{
			EOFException exp("End of file reached");
			throw exp;
		} // if
		return *this;
	} // ITDF


	itdf& itdf::operator>>(int& out)
	{
		eatwhite(m_inputStream);
		if(!m_inputStream.eof() && m_inputStream.good())
		{
			m_inputStream >> out;

			// remove trailing tab if it exists
			char c;
			m_inputStream.get(c);
			if(c != '\t')
			{
				m_inputStream.putback(c);
			} // if
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
	itdf& itdf::operator>>(string& out)
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
		} else 
		{
				EOFException exp("End of file reached");
				throw exp;
		} // if
		return *this;
	} // ITDF
	
} // archendale
