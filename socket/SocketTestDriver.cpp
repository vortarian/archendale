
#include <iostream>
#include "SocketObject.h"
#include "SocketAttribute.h"

using namespace archendale;

void main(void)
{
	SocketAttribute attr;
	Socket so(attr);

	so << "Testing";
};


