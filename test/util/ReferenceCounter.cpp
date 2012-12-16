#include <iostream>
#include <util/reference_counter.h>

using namespace std;
using namespace archendale;

// Used to test the derferencing operator
class Dereferenced
{
public:
	Dereferenced(int input = 0)
	{
		m_data = input;
	} // Dereferenced

	int getValue() { return m_data; }
	void setValue(int input) { m_data = input; }
private:

	int m_data;
}; // Dereferenced

int main(void)
{
	reference_counter<int>* rcptr = new reference_counter<int>(new int(0));

	{
		reference_counter<int> a(new int(3));

		// This block tests destruction
		{
			// Test Copy Constructor
			reference_counter<int> b = a;

			if(*b != 3)
			{
				cerr << "Test Failed! *b != 3, *b == " << *b << endl;
			}

			reference_counter<int> c;
			c = b;
			if(*c != 3)
			{
				cerr << "Test Failed! *c != 3, *c == " << *c << endl;
			}

			// Test operator =
			*c = 4;	
		} 

		if(*a != 4)
		{
			cerr << "Test Failed! *a != 4, *a == " << *a << endl;
		}

		// Test through pointer
		*rcptr = a;
	}

	if(**rcptr != 4)
	{
		cerr << "Test Failed! **rcptr != 4, **rcptr == " << **rcptr << endl;
		return -1;
	}

	reference_counter<Dereferenced> deref(new Dereferenced(4));

	deref->setValue(3);
	if(deref->getValue() != 3)
	{
		cerr << "Test Failed! deref->getValue() != 3, deref->getValue() == " << deref->getValue() << endl;
		return -1;
	}
		
	cout << "Test SUCCEEDED" << endl;
	return 0;
}
