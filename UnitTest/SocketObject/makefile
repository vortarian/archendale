
include ../../makefile.global

LINKEROPTIONS = -L../../lib -lpthread -lException -lThreadObject -lSocketObject
SOCKETDRIVEROBJECTS =  SocketTestDriver.o
SOCKETSERVEROBJECTS =  SocketServerTest.o
SOCKETCLIENTOBJECTS =  SocketClientTest.o
MULTITHREADEDSOCKETSERVEROBJECTS =  MultithreadedSocketServerTest.o

EXES = SocketTestDriver SocketServerTest SocketClientTest  MultithreadedSocketServerTest

.SUFFIXES = .cpp .h .c .o

all: $(EXES)

run: all
	-./SocketTestDriver

clean:
	-rm *\.o
	-rm $(EXES)
	
SocketTestDriver: $(SOCKETDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SOCKETDRIVEROBJECTS)  $(LINKEROPTIONS)

SocketServerTest: $(SOCKETSERVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SOCKETSERVEROBJECTS)  $(LINKEROPTIONS)

SocketClientTest: $(SOCKETCLIENTOBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SOCKETCLIENTOBJECTS)  $(LINKEROPTIONS)

MultithreadedSocketServerTest: $(MULTITHREADEDSOCKETSERVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(MULTITHREADEDSOCKETSERVEROBJECTS) $(LINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

