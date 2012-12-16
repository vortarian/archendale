#include <iostream>
#include <fstream>
#include <stdexcept>

#include <io/FileTable.h>
#include <io/ITDF.h>
#include <io/OTDF.h>
#include <io/IOException.h>
#include <exception/Exception.h>

using namespace std;
using std::ofstream;
using std::ifstream;

namespace archendale
{
	// FileTable:
	//
	template<class T> file_table<T>::file_table(const string& dataFile) : DATA_FILE(dataFile)
	{
		load();
	} // FileTable

	// FileTable:
	//
	template<class T> file_table<T>::file_table(const file_table& in) : vector<T>(in), DATA_FILE(in.DATA_FILE)
	{
	} // FileTable

	// ~FileTable:
	//
	template<class T> file_table<T>::~file_table()
	{
		save();
	} // ~FileTable

	// update:
	//	Update entries in the table
	//	If the entry does not exist, add an entry to the table
	//	Replace all \t's with TAB_REPLACE_SIZE spaces
	template<class T> void file_table<T>::update(T entry)
	{
		if(entry.m_isNew)
		{
			entry.m_id = size();
			push_back(entry);
		} else
		{
			this->operator[](entry.m_id) = entry;
		} // if
	} // update

	// remove:
	//	Remove an entry from the table
	template<class T> void file_table<T>::remove(const T& entry)
	{
		NotImplementedException exp;
		throw exp;
	} // update

	// save:
	//
	template<class T> void file_table<T>::save()
	{
		ofstream ofstr(DATA_FILE.c_str(), ios::trunc);
		if(!ofstr.is_open()) 
		{
			Exception exp("Unable to open file " + DATA_FILE + "for reading");
			throw exp;
		} // if

		// Create the output file
		otdf otdf(ofstr);

		vector<T>::const_iterator startIter = begin();
		vector<T>::const_iterator endIter = end();
		while(startIter != endIter)
		{
			otdf << *startIter;
			startIter++;
		} // while
	} // save

	// load:
	//	Loads the data from DATA_FILE, the file must exist first!
	//
	template<class T> void file_table<T>::load()
	{
		erase(begin(), end());
		ifstream ifstr(DATA_FILE.c_str());
		if(!ifstr.is_open()) 
		{
			Exception exp("Unable to open file " + DATA_FILE + " for writing");
			throw exp;
		} // if

		itdf itdf(ifstr);
		try 
		{	
			while(1)
			{
				T entry;
				itdf >> entry;
				push_back(entry);
			} // while
		} catch (EOFException exp)
		{
		} // try
	} // load
} // namespace archendale
