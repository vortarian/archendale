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


	class String  
	{
		friend ostream& operator<<(ostream&, const String&);

	public:
		// Constructors
		String();
		String(const char*, const unsigned int = 0);

		// Destructor
		virtual ~String();

		// Copy Constructor
		String(const String&);

		String& operator =(const String&);
		String operator()(unsigned int, unsigned int) const;
		
		bool isEqual(const String&, bool = false) const;

		// Logical Operators
		String& operator +=(const String&);
		String operator +(const String&) const;
		bool operator ==(const String&) const;
		bool operator !=(const String&) const;
		bool operator >(const String&) const;
		bool operator <(const String&) const;
		bool operator >=(const String&) const;
		bool operator <=(const String&) const;

		// Extraction Operators		
		ostream& operator<<(ostream&);
		
		// Methods
		bool shrink();
		const char* data() const;
		unsigned int length() const;
		unsigned int find(const String&, unsigned int = 0) const;
		bool setSize(const unsigned int);

		String subString(const unsigned int) const;
		String subString(const unsigned int, const unsigned int) const;
		// For tokenizing
		String subString(const String) const;
	private:
		char* m_data;		// String DataException
		unsigned int m_length;	// Length of String
	};
	
} // archendale

#endif // !defined(STRING_H)
