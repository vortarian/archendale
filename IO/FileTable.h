
#ifndef FileTable_H
#define FileTable_H

#include <vector>

using std::vector;

namespace archendale
{
	template<class T> class FileTable : public vector<T>
	{
	public:
		// FileTable:
		//
		FileTable(const string& dataFile);

		// FileTable:
		//
		FileTable(const FileTable<T>&);

		// ~FileTable:
		//
		virtual ~FileTable();
		
		// update
		//	Update entries in the table
		//	If the entry does not exist, add an entry to the table
		virtual void update(T);
	
		// delete
		// 	Remove an entry from the table
		//	Relies on operator== of T
		virtual void remove(const T&);

	private:
		const string DATA_FILE;

		// Saves the information to the Catalog Configuration File
		void save();
		
		// Loads the information from the Catalog Configuration File
		void load();
	}; // FileTable

} // namespace FantasyRealm

// Template clas
#include <FileTable.cc>

#endif // FileTable_H
