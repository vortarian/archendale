#include <iostream>
#include <Util/ReferenceCounter.h>

using namespace std;


int main(void)
{
	RefCount<int> a(3);
	RefCount<int> b = a;
	RefCount<int> c = b;

cout << "Assignment" << endl;
	*c = 4;	

	cout << "a: " << *a << endl;
	cout << "b: " << *b << endl;
	cout << "c: " << *c << endl;

	return 0;
}
