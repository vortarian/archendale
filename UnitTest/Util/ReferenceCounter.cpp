#include <iostream>
#include <Util/ReferenceCounter.h>

using namespace std;
using namespace archendale;

int main(void)
{
	RefCount<int>* rcptr = new RefCount<int>();

	{
		RefCount<int> a(3);

		// This block tests destruction
		{
			// Test Copy Constructor
			RefCount<int> b = a;

			if(*b != 3)
			{
				cerr << "Test Failed! *b != 3, *b == " << *b << endl;
			}

			RefCount<int> c;
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
	}

	cout << "Test SUCCEEDED" << endl;
	return 0;
}
