// String.cpp: implementation of the String class.
//
//////////////////////////////////////////////////////////////////////

#include <String/String.h>
#include <Exception/Exception.h>
#include <string.h>
#include <ctype.h>

using std::toupper;

namespace archendale
{

//////////////////////////////////////////////////////////////////////
// Global Operators
//////////////////////////////////////////////////////////////////////

	ostream& operator<<(ostream& out, const String& rhs) {
		out << rhs.m_data;
		return out;
	} // operator<<


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	String::String()
	{
		m_data = 0;
		m_length = 0;
		setSize(2);
		m_data[0] = '\0';
	}

	String::String(const char* data, const unsigned int length)
	{
		m_data = 0;
		m_length = 0;
		if(length == 0)
		{
			setSize(strlen(data) + 1);
			strcpy(m_data, data);
		} else {
			setSize(length + 1);
			strncpy(m_data, data, length);
			m_data[length] = '\0';
		}
	}

	String::~String()
	{
		delete[] m_data;
		m_data = 0;
	}

	String::String(const String& data)
	{
		m_data = 0;
		m_length = 0;
		setSize(strlen(data.m_data) + 1);
		strcpy(m_data, data.m_data);
	}

	String String::operator ()(unsigned int start, unsigned int end) const
	{
		char* data = new char[end - start];
		strncpy(data, m_data + start, end - start);
		String retValue(data);
		delete[] data;
		return retValue;
	}

	bool String::isEqual(const String& rhs, bool ignoreCase) const {
		if(true == ignoreCase) {
			char* ldata = new char[m_length];
			char* rdata = new char[rhs.m_length];

			unsigned int i = 0;
			for(i = 0; i < m_length - 1; i++) {
				ldata[i] = toupper(m_data[i]);
			} // for
			// Don't forget the \0
			ldata[i] = m_data[i];

			for(i = 0; i < rhs.m_length - 1; i++) {
				rdata[i] = toupper(rhs.m_data[i]);	
			} // for
			// Don't forget the \0
			rdata[i] = rhs.m_data[i];

			// Finally, the comparison
			bool retValue = String(ldata) == String(rdata);
			delete[] ldata;
			delete[] rdata;

			return retValue;
		} else {
			return *this == rhs;
		} // if
	} // compare

	String& String::operator +=(const String& data)
	{
		setSize(m_length + data.m_length);
		strcat(m_data, data.m_data);
		return *this;
	}

	String String::operator +(const String& data) const
	{
		String NewString(*this);
		NewString += data;
		return NewString;
	}

	String& String::operator =(const String& data)
	{
		delete[] m_data;
		m_data = 0;
		m_length = 0;
		setSize(strlen(data.m_data) + 1);
		strcpy(m_data, data.m_data);
		return *this;
	}

	bool String::operator ==(const String& data) const
	{
		if(m_length != data.m_length)
		{
			return false;
		} else 
		{
			int val = strcmp(m_data, data.m_data);
			if(val) return false;
			else return true;
		}
	}

	bool String::operator !=(const String& data) const
	{
		if(m_length != data.m_length)
		{
			return true;
		} else 
		{
			int val = strcmp(m_data, data.m_data);
			if(val) return true;
			else return false;
		}
	}

	bool String::operator >(const String& data) const
	{
		int val = strcmp(m_data, data.m_data);
		if(val > 0) return true;
		else return false;
	}

	bool String::operator <(const String& data) const
	{
		int val = strcmp(m_data, data.m_data);
		if(val < 0) return true;
		else return false;
	}

	bool String::operator >=(const String& data) const
	{
		int val = strcmp(m_data, data.m_data);
		if(val >= 0) return true;
		else return false;
	}

	bool String::operator <=(const String& data) const
	{
		int val = strcmp(m_data, data.m_data);
		if(val <= 0) return true;
		else return false;
	}

	ostream& String::operator <<(ostream& ostr)
	{
		return (ostr << m_data);
	}

	////////////////////
	// Public Methods
	////////////////////
	bool String::shrink()
	{
		unsigned int size = strlen(m_data) + 1;
		if(m_length == size) return true;

		char* temp = m_data;
		m_data = new char[size];

		// Should throw an exception
		if(m_data == 0) 
		{
			m_data = temp;
			return false;
		}
		m_length = size;
		strcpy(m_data, temp);
		delete[] temp;
		return true;
	}

	const char* String::data() const
	{
		return m_data;
	}

	unsigned int String::length() const
	{
		return m_length;
	}

	unsigned int String::find(const String& expr, unsigned int beginIndex) const
	{
		if(beginIndex >= length()) 
		{
			IndexOutOfBoundsException exp;
			throw exp;
		} // if
		if(expr.length() > length())
		{
			StringNotFoundException exp;
			throw exp;
		}
		do
		{
			if(length() < expr.length()) break;
			if(!strncmp(data() + beginIndex, expr.data(), expr.length() - 1))
			{
				return beginIndex;
			}
			beginIndex++;
		}while(beginIndex <= length() - expr.length());
		StringNotFoundException exp;
		throw exp;
	}

	String String::subString(unsigned int subStringLength) const
	{
		return subString(0, subStringLength);	
	}

	String String::subString(unsigned int startIndex, unsigned int subStringLength) const
	{
		if(startIndex > m_length)
		{
			IndexOutOfBoundsException exp;
			throw exp;
		} // if
		if(subStringLength > m_length - startIndex) subStringLength = m_length - startIndex;
		//char *temp = new char[subStringLength + 1];
		//strncpy(temp, data() + startIndex, subStringLength);
		//temp[subStringLength + 1] = '\0';
		cerr << "startIndex: " << startIndex << endl;
		cerr << "m_length: " << m_length << endl;
		cerr << "m_data: " << m_data << endl;
		cerr << "subStringLength: " << subStringLength << endl;
		String newStr(data() + startIndex, subStringLength);
		cout << newStr.data() << endl;
		//delete temp;
		return newStr;
	}

	String String::subString(const String token) const
	{
		NotImplementedException exp;
		throw exp;
	}

	bool String::setSize(const unsigned int size)
	{
		if(m_length == size) return true;
		if(size <= 1)
		{
			// Zero out the size, make it an empty string
			if(m_data != 0) delete[] m_data;
			m_data = new char[1];
			if(m_data == 0) return false;
			m_data[0] = '\0';
			m_length = 1;
		}
		if(m_data == 0)
		{
			m_data = new char[size];
			if(m_data == 0)
				return false;
			m_length = size;
		}else 
		{
			if(m_length > size) 
			{
				m_data[size - 1] = '\0';
			}
			char* temp = m_data;
			m_data = new char[size];

			// Should throw an exception
			if(m_data == 0)
			{
				m_data = temp;
				return false;
			}
			m_length = size;
			strcpy(m_data, temp);
		}
		return true;
	}
	////////////////////
	// Private Methods
	////////////////////

} // archendale

