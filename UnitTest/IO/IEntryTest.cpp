#include <IO/ITDF.h>
#include <IO/OTDF.h>
#include <IO/IEntry.h>
#include <Factory/Factory.h>
#include <iostream>
#include <sstream>

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

} // archendale

using namespace archendale;

stringstream iostr;

// entryFactory:
//	returns the next IEntry type object from the ITDF stream
IEntry* entryFactory(ITDF& in)
{
	string name;
cout << iostr.str().c_str() << endl;
	in >> name;
cout << iostr.str().c_str() << endl;
cout << name << endl;
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

int main(void)
{
	IntEntry ia(3);
	StringEntry sa("Hello World");
	
	OTDF otdf(iostr);	

	otdf << ia.getName() << ia << sa.getName() << sa;

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
	itdf >> *sb;
	
	if( (ia == *ib) && (sa == *sb) ) 
	{
		cout << "Test SUCCEEDED!" << endl;
	} else 
	{
		cout << "Test FAILED!" << endl;
	} // if
	delete ib;
	delete sb;
	tib = ib = 0;
	tsb = sb = 0;
} // main

