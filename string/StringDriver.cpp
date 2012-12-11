#include <iostream>
#include <string.h>
#include <strstream>

#include <string/String.h>

using archendale::String;

class TestException
{
// TODO: This exception will work great for all
//		exceptions _EXCEPT_ out of memory!
public:
	TestException(const char* why, const char* file = "", const int line = 0)
	{
		unsigned int length = strlen(why) + strlen(file) + 10;
		msg = new char[length];
		ostrstream stream(msg, length);
		stream << file << ":" << line << ":" << why << endl;
	}
	
	TestException(const TestException& lhv)
	{
		msg = new char[strlen(lhv.why())];
		if(msg == 0) throw -1;
		strcpy(msg, lhv.why());
	}
	
	~TestException()
	{
		delete[] msg;
	}
	
	const char* why() const
	{
		return msg;
	}
private:
	char* msg;
};

#define THROWTEXP(x) throw TestException(x, __FILE__, __LINE__)

void testConstructor()
{
	String noargs;
	if(0 != strcmp(noargs.data(), ""))
	{
		THROWTEXP("noargs != \"\"");
	}

	String args("Hello World");
	if(0 != strcmp(args.data(), "Hello World"))
	{
		THROWTEXP("Hello World");
	}
	cout << "testConstructors finished" << endl;
}

void testAssignment()
{
	String additionAssignmentTest;
	additionAssignmentTest += "Hello World";
	if(0 != strcmp(additionAssignmentTest.data(), "Hello World"))
	{
		THROWTEXP("Hello World");
	}
	

	String additionTest;
	additionTest = additionAssignmentTest + " How are you?";
	if(0 != strcmp(additionTest.data(), "Hello World How are you?"))
	{
		THROWTEXP("Hello World How are you?");
	}
	cout << "testAssignment finished" << endl;
}

void testLogicalOperators()
{
	String rat("World");

	if(!(rat == String("World")))
	{
		THROWTEXP("rat == World");
	}
	if(rat == "Worlds")
	{
		THROWTEXP("rat == Worlds");
	}

	if(!(rat != "World2"))
	{
		THROWTEXP("rat != World2");
	}
	if(rat != "World")
	{
		THROWTEXP("rat != World");
	}
	
	if(!(rat > "A"))
	{
		THROWTEXP("rat > A");
	}
	if(rat > "Z")
	{
		THROWTEXP("rat > Z");
	}
	
	if(!(rat < "Z"))
	{
		THROWTEXP("rat == Z");
	}
	if(rat < "A")
	{
		THROWTEXP("rat == Z");
	}

	if(!(rat >= "World"))
	{
		THROWTEXP("rat >= World");
	}
	if(!(rat >= "AWorld"))
	{
		THROWTEXP("rat >= AWorld");
	}
	if(rat >= "ZWorld")
	{
		THROWTEXP("rat >= AWorld");
	}

	if(!(rat <= "World"))
	{
		THROWTEXP("rat <= World");
	}
	if(!(rat <= "ZWorld"))
	{
		THROWTEXP("rat <= ZWorld");
	}
	if(rat <= "AWorld")
	{
		THROWTEXP("rat <= ZWorld");
	}
	cout << "testLogicalOperators finished" << endl;
}

void testShrink()
{
	String shrinker, shrinkempty;
	shrinker = "test";
	shrinker.shrink();
	shrinkempty.shrink();
	cout << "testShrink finished" << endl;
}

void testFind()
{
	using archendale::IndexOutOfBoundsException;
	using archendale::StringNotFoundException;
	
	String findOn("Test");
	String Begin("Te");
	String End("st");
	String Middle("es");
	String TooLong("Test1");
	String NotInTooLong("nofind");
	String NotIn("nd");
	
	try
	{
		if(0 != findOn.find(Begin))
		{
				THROWTEXP("Begin String not at the Beginning!");
		}
		if(2 != findOn.find(End))
		{
				THROWTEXP("Begin String not at the Beginning!");
		}
		if(1 != findOn.find(Middle))
		{
				THROWTEXP("Begin String not at the Beginning!");
		}
	} catch(StringNotFoundException exp)
	{
		THROWTEXP("Element Not Found Exception, Test Failed!");
	}
	
	try
	{
		findOn.find(TooLong);
	} catch(StringNotFoundException exp)
	{
		// Worked Fine Do Nothing
	}
	
	try
	{
		findOn.find(NotInTooLong);
	} catch(StringNotFoundException exp)
	{
		// Worked Fine Do Nothing
	}
	
	try
	{
		findOn.find(NotIn);
	} catch(StringNotFoundException exp)
	{
		// Worked Fine Do Nothing
	}
	
	// Multiple Searching
	findOn = "TestTest";
	unsigned int index = 0;

	try
	{
		findOn.find(Begin, 12);
	} catch(StringNotFoundException exp)
	{
		THROWTEXP("Element Not Found Exception, Test Failed!");
	} catch(IndexOutOfBoundsException exp)
	{
		// Worked Fine Do Nothing
	}
	
	index = 0;
	try
	{
		if(0 != (index = findOn.find(Begin)))
		{
			THROWTEXP("index != 0, Test Failed!");
		}
		if(4 != (index = findOn.find(Begin, index + 1)))
		{
			THROWTEXP("index != 4, Test Failed!");
		}
	} catch(StringNotFoundException exp)
	{
		THROWTEXP("Element Not Found Exception, Test Failed!");
	} catch(IndexOutOfBoundsException exp)
	{
		THROWTEXP("IndexOutOfBoundsException, Test Failed!");
	}
	cout << "testFind finished" << endl;
}

void main(void) 
{
	try
	{
		testConstructor();
		testAssignment();
		testLogicalOperators();
		testShrink();
		testFind();
	} catch(TestException exp)
	{
		cerr << "Caught Exception!" << endl;
		cerr << exp.why() << endl;
		return -1;
	} catch(int i)
	{
		if(i == -1)
		{
			cerr << "Exception thrown, and Out of Memory!  Exception has been lost!" << endl;
			return -1;
		}else cerr << "Unkown exception: " << i << endl;
	}
}
