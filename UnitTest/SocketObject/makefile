
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(GLOBALCCOPTIONS) $(INCLUDE) -D_REENTRANT -g
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
	
SocketTestDriver: $(SOCKETDRIVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(SOCKETDRIVEROBJECTS)  $(LINKEROPTIONS)

SocketServerTest: $(SOCKETSERVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(SOCKETSERVEROBJECTS)  $(LINKEROPTIONS)

SocketClientTest: $(SOCKETCLIENTOBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(SOCKETCLIENTOBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

