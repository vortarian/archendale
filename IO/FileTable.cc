
#include <fstream>
#include <FileTable.h>
#include <stdexcept>
#include <IO/ITDF.h>
#include <IO/OTDF.h>
#include <IO/IOException.h>
#include <Exception/Exception.h>
#include <iostream>

using namespace std;
using std::ofstream;
using std::ifstream;

namespace archendale
{
	// FileTable:
	//
	template<class T> FileTable<T>::FileTable(const string& dataFile) : DATA_FILE(dataFile)
	{
		load();
	} // FileTable

	// FileTable:
	//
	template<class T> FileTable<T>::FileTable(const FileTable& in) : vector<T>(in), DATA_FILE(in.DATA_FILE)
	{
	} // FileTable

	// ~FileTable:
	//
	template<class T> FileTable<T>::~FileTable()
	{
		save();
	} // ~FileTable

	// update:
	//	Update entries in the table
	//	If the entry does not exist, add an entry to the table
	//	Replace all \t's with TAB_REPLACE_SIZE spaces
	template<class T> void FileTable<T>::update(T entry)
	{
		string replaceText(TAB_REPLACE_SIZE, ' ');
		unsigned int startIndex = 0;
		try
		{
			while(string::npos != (startIndex = entry.m_name.find('\t', startIndex)))
			{
				entry.m_name.replace(startIndex, 1, replaceText);
			} // while
		} catch(out_of_range)
		{
			// They are all replaced if we get here
		} // try
		startIndex = 0;
		try
		{
			while(string::npos != (startIndex = entry.m_description.find('\t', startIndex)))
			{
				entry.m_description.replace(startIndex, 1, replaceText);
			} // while
		} catch (out_of_range)
		{
			// They are all replaced if we get here
		} // try
		
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
	template<class T> void FileTable<T>::remove(const T& entry)
	{
		NotImplementedException exp;
		throw exp;
	} // update

	// save:
	//
	template<class T> void FileTable<T>::save()
	{
		ofstream ofstr(DATA_FILE.c_str(), ios::trunc);
		if(!ofstr.is_open()) 
		{
			Exception exp("Unable to open file " + DATA_FILE + "for reading");
			throw exp;
		} // if

		// Create the output file
		OTDF otdf(ofstr);

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
	template<class T> void FileTable<T>::load()
	{
		erase(begin(), end());
		ifstream ifstr(DATA_FILE.c_str());
		if(!ifstr.is_open()) 
		{
			Exception exp("Unable to open file " + DATA_FILE + " for writing");
			throw exp;
		} // if

		ITDF itdf(ifstr);
		try 
		{	
			T entry;
			while(1)
			{
				itdf >> entry;
				push_back(entry);
			} // while
		} catch (EOFException exp)
		{
		} // try
	} // load
} // namespace archendale
