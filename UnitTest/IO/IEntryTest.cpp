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
const string IntEntry::m_className("IntEntry");

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
const string StringEntry::m_className("StringEntry");

} // archendale

using namespace archendale;

int main(void)
{
	IntEntry ia(3);
	IntEntry ib(0);
	StringEntry sa("Hello World");
	StringEntry sb("");
	
	stringstream iostr;
	OTDF otdf(iostr);	

	otdf << ia << sa;

	ITDF itdf(iostr);
	itdf >> ib >> sb;
	
	if( (ia == ib) && (sa == sb) ) 
	{
		cout << "Test SUCCEEDED!" << endl;
	} else 
	{
		cout << "Test FAILED!" << endl;
	} // if
} // main

