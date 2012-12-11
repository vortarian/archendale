
include ../../makefile.global

LINKEROPTIONS = -L../../lib -lpthread -lException -lThreadObject -lSocketObject
SOCKETDRIVEROBJECTS =  SocketTestDriver.o
SOCKETSERVEROBJECTS =  SocketServerTest.o
SOCKETCLIENTOBJECTS =  SocketClientTest.o
MULTITHREADEDSOCKETSERVEROBJECTS =  MultithreadedSocketServerTest.o
FILECOPYCLIENTOBJECTS =  FileCopyClient.o
FILECOPYSERVEROBJECTS =  FileCopyServer.o
SENDEMAILCLIENTOBJECTS =  SendEmailClient.o

EXES = SocketTestDriver SocketServerTest SocketClientTest  MultithreadedSocketServerTest FileCopyClient FileCopyServer SendEmailClient

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

FileCopyClient: $(FILECOPYCLIENTOBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(FILECOPYCLIENTOBJECTS) $(LINKEROPTIONS)

FileCopyServer: $(FILECOPYSERVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(FILECOPYSERVEROBJECTS) $(LINKEROPTIONS)

SendEmailClient: $(SENDEMAILCLIENTOBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SENDEMAILCLIENTOBJECTS) $(LINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

