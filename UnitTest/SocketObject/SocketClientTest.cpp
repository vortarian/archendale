#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <string>

#include <SocketObject/NameResolver.h>
#include <SocketObject/InternetAddress.h>
#include <SocketObject/SocketException.h>
#include <SocketObject/SocketObject.h>
#include <SocketObject/INETSocket.h>
#include <SocketObject/SocketServer.h>

using namespace std;
using std::string;
using namespace archendale;

//////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////

main(void)
{
	InternetAddress addr = NameResolver::getAddress("localhost");
	string data, rdata;
	INETSocket socket(addr, 5000);

	cout << "Getting connection" << endl;
	socket.connect();

	cout << "Have Connection, enter data: " << endl;
	cin >> data;
	socket << data << SocketObject::transmit;
	cout << "Sending: " << data << endl;
	socket >> rdata;
	cout << "Recieved: " << rdata << endl;
	if(rdata == data) cout << "Succeeded!!!!!!!" << endl;
	else cout << "Failed!" << endl;
} // main
