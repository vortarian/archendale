
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(GLOBALCCOPTIONS) $(INCLUDE) -D_REENTRANT -g
LINKEROPTIONS = -L../../lib -lpthread -lException -lString -lThreadObject -lSocketObject
SOCKETDRIVEROBJECTS =  SocketTestDriver.o

.SUFFIXES = .cpp .h .c .o

all: SocketTestDriver

run: all
	-./SocketTestDriver

clean:
	-rm *\.o
	-rm SocketTestDriver
	
SocketTestDriver: $(SOCKETDRIVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(SOCKETDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

