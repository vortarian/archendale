#include <IO/ITDF.h>
#include <IO/OTDF.h>
#include <IO/IOException.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace archendale;

bool ITDFRead()
{
	cout << "Running ITDFRead" << endl;

	string testString;
	stringstream istr(testString);
	double dInput = 0;
	int iInput = 0;
	string sInput = "";

	OTDF otdf(istr);

	otdf << 32.5;
	otdf << "Hello World";
	otdf << 48;
	otdf << 33;
	otdf << "Howdy";
	otdf << 44;

	ITDF itdf(istr);

	try 
	{ 

		itdf >> dInput;
		cout << dInput << endl;
		if(dInput != 32.5)
		{
			cout << "test failed:if(dInput != 32.5) " << endl;
			return false;
		} // if

		itdf >> sInput;
		cout << sInput << endl;
		if(sInput != "Hello World")
		{
			cout << "test failed:if(sInput != Hello     World) " << endl;
			return false;
		} // if

		itdf >> iInput;
		cout << iInput << endl;
		if(iInput != 48)
		{
			cout << "test failed:if(iInput != 48) " << endl;
			return false;
		} // if

		itdf >> dInput;
		cout << dInput << endl;
		if(dInput != 33)
		{
			cout << "test failed:if(dInput != 33) " << endl;
			return false;
		} // if

		itdf >> sInput;
		cout << sInput << endl;
		if(sInput != "Howdy")
		{
			cout << "test failed:if(sInput != Howdy) " << endl;
			return false;
		} // if

		itdf >> dInput;
		cout << dInput << endl;
		if(dInput != 44)
		{
			cout << "test failed:if(dInput != 33) " << endl;
			return false;
		} // if
	} catch (EOFException exp)
	{
		cerr << "Caught unexpted EOFException" << endl;
		return false;
	}
	
	// Try a double read that is bad
	try 
	{
		itdf >> dInput;
		cerr << "Did not catch expected EOFException" << endl;
		return false;
	} catch (EOFException exp)
	{
		// Should have caught this one
	}
	
	// Try a string read that is bad
	try 
	{
		itdf >> sInput;
		cerr << "Did not catch expected EOFException" << endl;
		return false;
	} catch (EOFException exp)
	{
		// Should have caught this one
	}
	//
	// Now, see what happens if we try to read a double and the next value is a string
	testString = "String";
	stringstream istr2(testString);
	ITDF itdf2(istr2);
	try
	{
		dInput = 0;
		itdf2 >> dInput;
		if(dInput != 0) 
		{	
			cerr << "Test Failed error " __FILE__ ":" << __LINE__ << endl;
			return false;
		} // if
		
		sInput = "";
		itdf2 >> sInput;
		if(sInput != "String")
		{	
			cerr << "Test Failed error " __FILE__ ":" << __LINE__ << endl;
			return false;
		} // if
	} catch (EOFException exp)
	{
		cout << "Caught the correct exception (GOOD)" << endl;
		// Should catch some Exception here
	} // try
	
	cout << "ITDFRead SUCCEEDED" << endl;
	return true;
} // ITDFRead

int main(void)
{
	if(!ITDFRead())
	{
		cerr << "ITDFRead FAILED" << endl;
	} // if

} // main
