// String.h: interface for the String class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(STRING_H)
#define STRING_H

#include <iostream>
using std::ostream;

namespace archendale
{
	// String Exceptions will not inherit from the Exception Class
	// as they cause a circular dependency which throws an error
	// in g++
	
	// Exceptions
	class StringNotFoundException	
	{
	};

	class IndexOutOfBoundsException
	{
	};

	class string  
	{
		friend ostream& operator<<(ostream&, const string&);

	public:
		// Constructors
		string();
		string(const char*, const unsigned int = 0);

		// Destructor
		virtual ~string();

		// Copy Constructor
		string(const string&);

		string& operator =(const string&);
		string operator()(unsigned int, unsigned int) const;
		
		bool isEqual(const string&, bool = false) const;

		// Logical Operators
		string& operator +=(const string&);
		string operator +(const string&) const;
		bool operator ==(const string&) const;
		bool operator !=(const string&) const;
		bool operator >(const string&) const;
		bool operator <(const string&) const;
		bool operator >=(const string&) const;
		bool operator <=(const string&) const;

		// Extraction Operators		
		ostream& operator<<(ostream&);
		
		// Methods
		bool shrink();
		const char* data() const;
		unsigned int length() const;
		unsigned int find(const string&, unsigned int = 0) const;
		bool setSize(const unsigned int);

		string subString(const unsigned int) const;
		string subString(const unsigned int, const unsigned int) const;
		// For tokenizing
		string subString(const string) const;
	private:
		char* m_data;		// String DataException
		unsigned int m_length;	// Length of String
	};
	
} // archendale

#endif // !defined(STRING_H)
