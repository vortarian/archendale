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
	ostream& writeData(ostream& out) const
	{
		return out << m_data; 
	} // writeData
	
	istream& readData(istream& in)
	{
		return in >> m_data;
	} // readData
	
	bool operator==(const IntEntry& rhs) const
	{
		return m_data == rhs.m_data;
	} // operator ==
private:
	int m_data;
	static FactoryRegistrar<IntEntry> CFR;
}; // IntEntry

FactoryRegistrar<IntEntry> IntEntry::CFR("IntEntry");

class StringEntry : public IEntry
{
public:
	StringEntry() { ; }
	StringEntry(string data) { m_data = data; }
	~StringEntry() { ; }
	static void* newInstance() { return new StringEntry; }
	ostream& writeData(ostream& out) const
	{
		return out << m_data; 
	} // writeData
	
	istream& readData(istream& in)
	{
		return getline(in, m_data);
	} // readData
	
	bool operator==(const StringEntry& rhs) const
	{
		return m_data == rhs.m_data;
	} // operator ==
private:
	string m_data;
	static FactoryRegistrar<StringEntry> CFR;
}; // StringEntry

FactoryRegistrar<StringEntry> StringEntry::CFR("IntEntry");

} // archendale

using namespace archendale;

int main(void)
{
	IntEntry ia(3);
	IntEntry ib(0);
	StringEntry sa("Hello World");
	StringEntry sb("");
	
	string storedData;
	stringstream iostr(storedData);

	cout << "Stored Data: " << storedData << endl;

	cout << "Writing to Storage Data: ia:\"" << ia << "\" and sa:\"" << sa << "\"" << endl << endl;
	iostr << ia << sa;
	
	cout << "Stored Data: " << storedData << endl;
	cout << "Reading from Storage Data" << endl << endl;
	iostr >> ib >> sb;
	
	if( (ia == ib) && (sa == sb) ) 
	{
		cout << "Test SUCCEEDED! ib == \"" << ib << "\" and sb == \"" << sb << "\"" << endl;
	} else 
	{
		cout << "Test FAILED! ib == \"" << ib << "\" and sb == \"" << sb << "\"" << endl;
	} // if
} // main

