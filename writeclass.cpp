#include <iostream>
#include <fstream>
#include <String/String.h>

using namespace std;
using namespace archendale;

void printHeader(String file)
{
	String name = file;
	file = file + ".h";
	ofstream ostr(file.data());
	ostr << endl 
		<< "#ifndef " << name << "_H" << endl
		<< "#define " << name << "_H" << endl
		<< endl
		
		<< "namespace archendale" << endl
		<< "{" << endl
		<< "\t" << "class " << name.data() << endl 
		<< "\t" << "{" << endl
		<< "\t" << "public:" << endl

		<< "\t" << "\t" << "// " << name.data() << ":" << endl
		<< "\t" << "\t" << "//" << endl
		<< "\t" << "\t" << name.data() << "();" << endl
		<< endl

		<< "\t" << "\t" << "// " << name.data() << ":" << endl
		<< "\t" << "\t" << "//" << endl
		<< "\t" << "\t" << name.data() << "(const " << name.data() << "&);" << endl
		<< endl

		<< "\t" << "\t" << "// ~" << name.data() << ":" << endl
		<< "\t" << "\t" << "//" << endl
		<< "\t" << "\t" << "virtual ~" << name.data() << "();" << endl
		<< endl
		<< "\t" << "private:" << endl
		
		<< "\t" << "}; // " << name.data() << endl
		<< "} // namespace archendale" << endl
		<< endl
		<< "#endif " << "// "<< name << "_H" << endl;
		
}

void printSource(String file)
{
	String name = file;
	file = file + ".cpp";
	ofstream ostr(file.data());
	ostr << endl 
	
		<< "#include <SocketObject/" << name.data() << ".h>" << endl	
		<< endl
		<< "namespace archendale" << endl
		<< "{" << endl

		<< "\t" << "// " << name.data() << ":" << endl
		<< "\t" << "//" << endl
		<< "\t" << name.data() << "::" << name.data() << "()" << endl
		<< "\t" << "{" << endl
		<< "\t" << "} // " << name.data() << endl << endl

		<< "\t" << "// " << name.data() << ":" << endl
		<< "\t" << "//" << endl
		<< "\t" << name.data() << "::" << name.data() << "(const " << name.data() << "& in)" << endl
		<< "\t" << "{" << endl
		<< "\t" << "} // " << name.data() << endl << endl

		<< "\t" << "// ~" << name.data() << ":" << endl
		<< "\t" << "//" << endl
		<< "\t" << name.data() << "::~" << name.data() << "()" << endl
		<< "\t" << "{" << endl
		
		<< "\t" << "} // ~" << name.data() << endl << endl
		<< "} // namespace archendale" << endl;
}

int main(int arguementCount, char **argumentArray)
{
	try {
		String file;
		for(int i = 1; i < arguementCount; i++) 
		{
			file = argumentArray[i];
			printHeader(file);
			printSource(file);
		} // for
	} catch (IndexOutOfBoundsException exp)
	{
		cerr << "Caught Index out of bounds Exception" << endl;
	} catch (...)
	{
		cerr << "Caught unknown Exception" << endl;
	}
} // main


