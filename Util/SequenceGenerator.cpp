
#include <Util/SequenceGenerator.h>

using namespace std;

namespace archendale
{

	const string SequenceGenerator::m_className("SequenceGenerator");
	FactoryRegistrar<SequenceGenerator> SequenceGenerator::CFR("SequenceGenerator");

	// SequenceGenerator:
	//
	SequenceGenerator::SequenceGenerator()
	{
	} // SequenceGenerator

	// SequenceGenerator:
	//
	SequenceGenerator::SequenceGenerator(const SequenceGenerator& in)
	{
		m_data = in.m_data;
	} // SequenceGenerator

	// ~SequenceGenerator:
	//
	SequenceGenerator::~SequenceGenerator()
	{
	} // ~SequenceGenerator

	// findSequence:
	//	Locate a given sequence in the data, 
	//	return an iterator at that point
	//	return the end() if none found
	vector<SequenceGenerator::Entry>::iterator SequenceGenerator::findSequence(const string& searchValue) throw(ObjectNotFoundException)
	{
		vector<Entry>::iterator start =  m_data.begin();
		vector<Entry>::iterator end = m_data.end();
		while(start != end)
		{
			if(start->m_name == searchValue) return start;
			else start++;
		} // while
		ObjectNotFoundException exp(searchValue);
		throw exp;
		return end;
	} // findSequence

	// getNext:
	//	Returns the next value in the sequence
	int SequenceGenerator::getNext(const string& sequenceName) throw(ObjectNotFoundException)
	{
		return findSequence(sequenceName)->m_value++;
	} // getNext

	// addSequence:
	//	Creates a new Sequence
	void SequenceGenerator::addSequence(const string& sequenceName)
	{
		try
		{
			vector<Entry>::iterator seq = findSequence(sequenceName);
		} catch (ObjectNotFoundException exp)
		{
			Entry entry;
			entry.m_name = sequenceName;
			entry.m_value = 0;
			m_data.push_back(entry);
		} // try
	} // addSequence

	// removeSequence:
	//	Removes an existing Sequence
	void SequenceGenerator::removeSequence(const string& sequenceName) throw (ObjectNotFoundException)
	{
		m_data.erase(findSequence(sequenceName));
	} // removeSequence

	// writeData:
	// 	Write class data to the stream
	OTDF& SequenceGenerator::writeData(OTDF& out) const
	{
		out << m_data.size();
		vector<Entry>::const_iterator start = m_data.begin();
		vector<Entry>::const_iterator end = m_data.end();

		while(start != end)
		{
			out << start->m_name << start->m_value;
			start++;
		} // while
	} // writeData

	// readData:
	// 	Read class data from the stream
	ITDF& SequenceGenerator::readData(ITDF& in)
	{
		int size = 0;
		in >> size;

		Entry entry;
		for(int i = 0; i < size; i++)
		{
			in >> entry.m_name >> entry.m_value;
			m_data.push_back(entry);
		} // for
	} // readData

} // namespace archendale
