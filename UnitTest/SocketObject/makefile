
include ../../makefile.global

LINKEROPTIONS = -L../../lib -lpthread -lException -lThreadObject -lSocketObject
SOCKETDRIVEROBJECTS =  SocketTestDriver.o
SOCKETSERVEROBJECTS =  SocketServerTest.o
SOCKETCLIENTOBJECTS =  SocketClientTest.o

.SUFFIXES = .cpp .h .c .o

all: SocketTestDriver SocketServerTest SocketClientTest

run: all
	-./SocketTestDriver

clean:
	-rm *\.o
	-rm SocketTestDriver
	-rm SocketClientTest
	-rm SocketServerTest
	
SocketTestDriver: $(SOCKETDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SOCKETDRIVEROBJECTS)  $(LINKEROPTIONS)

SocketServerTest: $(SOCKETSERVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SOCKETSERVEROBJECTS)  $(LINKEROPTIONS)

SocketClientTest: $(SOCKETCLIENTOBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SOCKETCLIENTOBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

