
#ifndef SequenceGenerator_H
#define SequenceGenerator_H

#include <vector>
#include <string>
#include <io/IEntry.h>
#include <factory/Factory.h>

namespace archendale
{
	class SequenceGenerator : public IEntry
	{
	public:
		// SequenceGenerator:
		//
		SequenceGenerator();

		// SequenceGenerator:
		//
		SequenceGenerator(const SequenceGenerator&);

		// ~SequenceGenerator:
		//
		virtual ~SequenceGenerator();

		// getNext:
		//	Returns the next value in the sequence
		int getNext(const std::string&) throw (ObjectNotFoundException);

		// addSequence:
		//	Creates a new Sequence
		void addSequence(const std::string&);

		// removeSequence:
		//	Removes an existing Sequence
		void removeSequence(const std::string&) throw (ObjectNotFoundException);

		// getName:
		// Returns the name of this class	
		const string& getName() { return m_className; }
	
		// newInstance:	
		// Returns a new instance of this class
		static void* newInstance() { return new SequenceGenerator; }

		// writeData:
		// 	Write class data to the stream
		OTDF& writeData(OTDF& out) const;
	
		// readData:
		// 	Read class data from the stream
		ITDF& readData(ITDF& in);

	private:	
		class Entry
		{
		public:
			bool operator==(const Entry& rhs) const
			{
				return m_name == rhs.m_name;
			} // operator ==

			string m_name;
			int m_value;
		}; // Entry

		std::vector<Entry> m_data;

		// findSequence:
		//	Locate a given sequence in the data, 
		//	return an iterator at that point
		//	return the end() if none found
		std::vector<Entry>::iterator findSequence(const std::string&) throw (ObjectNotFoundException);

		static FactoryRegistrar<SequenceGenerator> CFR;
		static const std::string m_className;
	}; // SequenceGenerator
} // namespace archendale

#endif // SequenceGenerator_H
