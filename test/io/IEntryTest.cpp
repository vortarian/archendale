#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>

#include <io/itdf.h>
#include <io/otdf.h>
#include <io/ientry.h>
#include <factory/factory.h>

using namespace std;

namespace archendale
{

class IntEntry : public IEntry
{
public:
	IntEntry() { ; }
	IntEntry(int data) { m_data = data; }
	~IntEntry() { ; }
	static void* newInstance() { return new IntEntry; }
	OTDF& writeData(OTDF& out) const
	{
		return out << m_data; 
	} // writeData
	
	ITDF& readData(ITDF& in)
	{
		return in >> m_data;
	} // readData
	
	bool operator==(const IntEntry& rhs) const
	{
		if(!IEntry::operator==(rhs)) return false;
		return m_data == rhs.m_data;
	} // operator ==
	
	const string& getName() { return m_className; }
	
private:
	int m_data;
	const static string m_className;
	static FactoryRegistrar<IntEntry> CFR;
}; // IntEntry

FactoryRegistrar<IntEntry> IntEntry::CFR("IntEntry");
const string IntEntry::m_className = "IntEntry";

class StringEntry : public IEntry
{
public:
	StringEntry() { ; }
	StringEntry(string data) { m_data = data; }
	~StringEntry() { ; }
	static void* newInstance() { return new StringEntry; }
	OTDF& writeData(OTDF& out) const
	{
		return out << m_data; 
	} // writeData
	
	ITDF& readData(ITDF& in)
	{
		return in >> m_data;
	} // readData
	
	bool operator==(const StringEntry& rhs) const
	{
		if(!IEntry::operator==(rhs)) return false;
		return m_data == rhs.m_data;
	} // operator ==
	
	const string& getName() { return m_className; }
private:
	string m_data;
	const static string m_className;
	static FactoryRegistrar<StringEntry> CFR;
}; // StringEntry

FactoryRegistrar<StringEntry> StringEntry::CFR("StringEntry");
const string StringEntry::m_className = "StringEntry";

class HeterogenusEntry : public IEntry
{
public:
	HeterogenusEntry() { ; }
	HeterogenusEntry(string data) { m_data = data; }
	~HeterogenusEntry() { ; }
	static void* newInstance() { return new HeterogenusEntry; }
	OTDF& writeData(OTDF& out) const
	{
		out << int(m_strings.size());
		vector<string>::const_iterator start = m_strings.begin();
		while(start != m_strings.end())
		{
			out << *start;
			start++;
		} // while
		return out << m_data; 
	} // writeData
	
	ITDF& readData(ITDF& in)
	{
		int size = 0;
		in >> size;
		string entry;
		for(int i = 0; i < size; i++)
		{
			in >> entry;
			m_strings.push_back(entry);
		} // for
	 	in >> m_data;
		return in;
	} // readData
	
	bool operator==(const HeterogenusEntry& rhs) const
	{
		if(!IEntry::operator==(rhs)) return false;
		if(m_data != rhs.m_data) return false;
		if(m_strings.size() != rhs.m_strings.size()) return false;
		vector<string>::const_iterator start = m_strings.begin();
		vector<string>::const_iterator rhsStart = rhs.m_strings.begin();
		while(start != m_strings.end())
		{
			if(*start != *rhsStart) return false;
			start++;
			rhsStart++;
		} // while
		return true;
	} // operator ==

	void addString(const string& entry)
	{
		m_strings.push_back(entry);	
	} // addString

	vector<string>::iterator begin() 
	{
		return m_strings.begin();
	} // begin

	vector<string>::iterator end()
	{
		m_strings.end();
	} // end

	const string& getName() { return m_className; }
private:
	vector<string> m_strings;
	string m_data;
	const static string m_className;
	static FactoryRegistrar<HeterogenusEntry> CFR;
}; // HeterogenusEntry

FactoryRegistrar<HeterogenusEntry> HeterogenusEntry::CFR("HeterogenusEntry");
const string HeterogenusEntry::m_className = "HeterogenusEntry"; 

} // archendale

using namespace archendale;

// entryFactory:
//	returns the next IEntry type object from the ITDF stream
IEntry* entryFactory(ITDF& in)
{
	string name;
	in >> name;
	void *ptr = 0;
	try
	{
		ptr = Factory::createInstance(name);
	} catch (ClassNotFoundException exp)
	{
		cout << "ClassNotFoundException: " << exp.why() << endl << "File: " __FILE__ << ":" << __LINE__ << endl;
	} // try
	// So, you have to wonder why the static cast , and then the dynamic cast
	//	Let me tell you, dynamic_cast can not accept void*, and static_cast can
	//	by casting to what I think it is with static, I get to a class pointer,
	//	which dynamic_cast can take.  Then, the dynamic_cast checks to be sure the
	//	type is correct, if it is not, then 0 is returned here.  Keep in mind that
	//	static_cast has no runtime overhead
	return dynamic_cast<IEntry*>(static_cast<IEntry*>(ptr));
} // entryFactory

// TODO: Try it with a Templatized Entry

int main(void)
{
	try 
	{
		IntEntry ia(3);
		StringEntry sa("Hello World");
		HeterogenusEntry hsa("HelloHetero World");

		hsa.addString("One");
		hsa.addString("Two");
		hsa.addString("Three");
		hsa.addString("Four");
		
		stringstream iostr;
		OTDF otdf(iostr);	

		otdf << ia.getName() << ia << sa.getName() << sa << hsa.getName() << hsa;

		ITDF itdf(iostr);
		IEntry* tib = entryFactory(itdf);	// get the IntEntry

		// Test the types:
		if(0 == tib)
		{
			cout << "null pointers, tib is not valid" << endl;
			cout << "Test FAILED" << endl;
			return -1;
		} // if
		IntEntry* ib = dynamic_cast<IntEntry*>(tib);

		// I have no idea on earth why this could be wrong here, and right above, but
		// since this is a unit test, I will do it again
		// Test the types:
		if(0 == ib)
		{
			cout << "null pointers, tib is not valid" << endl;
			cout << "Test FAILED" << endl;
			return -1;
		} // if
		
		// Finally, read the object
		itdf >> *ib;
		
		IEntry* tsb = entryFactory(itdf);	// get the StringEntry
		if(0 == tsb)
		{
			cout << "null pointers, tsb is not valid" << endl;
			cout << "Test FAILED" << endl;
			return -1;
		} // if
		
		StringEntry* sb = dynamic_cast<StringEntry*>(tsb);
		if(0 == sb)
		{
			cout << "null pointers, tsb is not valid" << endl;
			cout << "Test FAILED" << endl;
			return -1;
		} // if
		
		// Read the string object
		itdf >> *sb;
		
		IEntry* htsb = entryFactory(itdf);	// get the HeterogenusEntry
		if(0 == htsb)
		{
			cout << "null pointers, htsb is not valid" << endl;
			cout << "Test FAILED" << endl;
			return -1;
		} // if
		
		HeterogenusEntry* hsb = dynamic_cast<HeterogenusEntry*>(htsb);
		if(0 == hsb)
		{
			cout << "null pointers, hsb is not valid" << endl;
			cout << "Test FAILED" << endl;
			return -1;
		} // if
		
		// Read the string object
		itdf >> *hsb;
		

		if( 
			// Test to see if the Int's are equal
			(ia == *ib) && 

			// Test to see if the Strings's are equal
			(sa == *sb) && 

			// Test to see if the Hetero's are equal
			(hsa == *hsb) && 

			// Test to see if the base class operator==
			// is working, it should be false
			!(*tib == *tsb)
		) 
		{
			cout << "Test SUCCEEDED!" << endl;
		} else 
		{
			cout << "Test FAILED!" << endl;
		} // if

		delete ib;
		delete sb;
		delete hsb;
		tib = ib = 0;
		tsb = sb = 0;
		htsb = hsb = 0;
	} catch (ObjectNotFoundException exp)
	{
		cerr << "Caught ObjectNotFoundException on object: " << exp.why() << endl;
		return -1;
	} // try
	return 0;
} // main

