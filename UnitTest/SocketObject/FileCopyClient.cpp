#include <iostream>
#include <fstream>
#include <sstream>
#include <SocketObject/INETSocket.h>
#include <SocketObject/NameResolver.h>

using namespace std;
using namespace archendale;

int main(void)
{
	int port = 6000;
	try
	{
		string filename, remoteFileName, remoteHostName;
		
		cout << "Please input the name of the file to copy: ";
		getline(cin, filename);
		cout << endl << endl;
		
		cout << "Please input the remote name of the file: ";
		getline(cin, remoteFileName);
		cout << endl << endl;
		
		cout << "Please input the name of the host to copy to: ";
		getline(cin, remoteHostName);
		cout << endl << endl;

		InternetAddress addr = NameResolver::getAddress(remoteHostName);
		INETSocket socket(addr, port);
                try
                {
                        socket.connect();
                } catch (ConnectionRefusedException exp)
                {
                        cerr << "Connection to port " 
				<< port 
				<< " was refused, is the FileCopyServer"
				<< " running on " 
				<< remoteHostName 
				<< "?" 
				<< endl;
                        return -1;
                } // try

		ifstream istr(filename.c_str());
		if(!istr)
		{
			cerr 	<< "Could not open " 
				<< filename 
				<< " for reading" 
				<< endl;
				return -1;
		} // if
		stringstream sostr;
		char ch;
		while(istr.get(ch)) sostr.put(ch);
		size_t fileSize = sostr.str().size();
		cout << "Sending file of size " << fileSize << endl;
		socket << remoteFileName << fileSize << sostr.str() << SocketObject::transmit;	
		cout << "File sent, exiting" << endl;	
	} catch (Exception& exp)
	{
		cerr	<< "Exception caught: " 
			<< endl
			<< "\ttype: " 
			<< typeid(exp).name() 
			<< endl
			<< "\twhy: " 
			<< exp.why() 
			<< endl;
		return -1;
	} // try
	return 0;
} // main
