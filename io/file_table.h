
#ifndef FileTable_H
#define FileTable_H

#include <vector>

using std::vector;

namespace archendale
{
	template<class T> class file_table : public vector<T>
	{
	public:
		// FileTable:
		//
		file_table(const string& dataFile);

		// FileTable:
		//
		file_table(const file_table<T>&);

		// ~FileTable:
		//
		virtual ~file_table();
		
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
#include <io/file_table.cc>

#endif // FileTable_H
