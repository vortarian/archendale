#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include <socket/inet.h>
#include <socket/name_resolver.h>

using namespace std;
using namespace archendale;

int main(void)
{
	int port = 25;
	try
	{
		string emailAddressTo, emailAddressFrom, hostname, subject, content;
		
		cout << "Please input your email address: ";
		getline(cin, emailAddressFrom);
		cout << endl << endl;
		
		cout << "Please input the recipient's address: ";
		getline(cin, emailAddressTo);
		cout << endl << endl;
		
		cout << "Please input the mail server to send with: ";
		getline(cin, hostname);
		cout << endl << endl;
	
		cout << "Please input the subject: ";
		getline(cin, subject);
		cout << endl << endl;
	
		cout << "Please input the message (carriage return to send): ";
		getline(cin, content);
		cout << endl << endl;

		internet_address addr = name_resolver::getAddress(hostname);
		inet socket(addr, port);
                try
                {
                        socket.connect();
                } catch (ConnectionRefusedException exp)
                {
                        cerr << "Connection to port " 
				<< port 
				<< " running on " 
				<< hostname
				<< " was refused"
				<< endl;
                        return -1;
                } // try

		cout << "sending" << endl;

		string remoteReply;
		socket.getline(remoteReply, '\n');
		cout << remoteReply << endl;

		socket << "HELO " << hostname << "\r\n" << socket::transmit;
		socket.getline(remoteReply, '\n');
		cout << remoteReply << endl;

		socket << "MAIL FROM: " << emailAddressFrom << "\r\n" << socket::transmit;
		socket.getline(remoteReply, '\n');
		cout << remoteReply << endl;

		socket << "RCPT TO: " << emailAddressTo << "\r\n" << socket::transmit;
		socket.getline(remoteReply, '\n');
		cout << remoteReply << endl;

		socket << "DATA\n" << content << "\r\n" << ".\r\n" << socket::transmit;
		socket.getline(remoteReply, '\n');
		cout << remoteReply << endl;

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
