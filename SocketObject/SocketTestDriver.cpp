
#include <iostream>
#include "SocketObject.h"
#include "SocketAttribute.h"

using namespace archendale;

void main(void)
{
	SocketAttribute attr;
	SocketObject so(attr);

	so << "Testing";
};


