#include <iostream>
#include <fstream>
#include <String/String.h>

using namespace std;
using namespace archendale;

void printHeader(String file)
{
	String name = file.subString(file.find(".h"));
	ofstream ostr(file.data());
	ostr << endl 
		<< "#ifndef " << file << endl
		<< "#define " << file << endl
		<< endl
		
		<< "namespace archendale" << endl
		<< "{" << endl
		<< "\t" << "class " << name.data() << endl 
		<< "\t" << "{" << endl

		<< "\t" << "\t" << "// " << name.data() << ":" << endl
		<< "\t" << "\t" << "//" << endl
		<< "\t" << "\t" << name.data() << "();" << endl
		<< endl

		<< "\t" << "\t" << "// ~" << name.data() << ":" << endl
		<< "\t" << "\t" << "//" << endl
		<< "\t" << "\t" << "~" << name.data() << "();" << endl
		<< endl
		
		<< "\t" << "}; // " << name.data() << endl
		<< "} // namespace archendale" << endl;
		
}

void printSource(String file)
{
	String name = file.subString(file.find(".cpp"));
	ofstream ostr(file.data());
	ostr << endl 
	
		<< "#include <SocketObject/" << name.data() << ".h>" << endl	
		<< "namespace archendale" << endl
		<< "{" << endl

		<< "\t" << "// " << name.data() << ":" << endl
		<< "\t" << "//" << endl
		<< "\t" << name.data() << "::" << name.data() << "()" << endl
		<< "\t" << "{" << endl
		<< "\t" << "} // " << name.data() << endl << endl

		<< "\t" << "// ~" << name.data() << ":" << endl
		<< "\t" << "//" << endl
		<< "\t" << name.data() << "::~" << name.data() << "()" << endl
		<< "\t" << "{" << endl
		
		<< "\t" << "} // ~" << name.data() << endl << endl
		<< "} // namespace archendale" << endl;
	cerr << "destroying ostr" << endl;
	ostr.~ofstream();
	cerr << "destroying name" << endl;
	name.~String();
	cerr << "leaving printSource" << endl;
}

void main(unsigned int arguementCount, char **argumentArray)
{
	try {
		String file;
		for(int i = 1; i < arguementCount; i++) 
		{
			file = argumentArray[i];
			printHeader(file + ".h");
			printSource(file + ".cpp");
		} // for
	} catch (IndexOutOfBoundsException exp)
	{
		cerr << "Caught Index out of bounds Exception" << endl;
	} catch (...)
	{
		cerr << "Caught unknown Exception" << endl;
	}
} // main


