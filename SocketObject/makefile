#########################################################
# makefile


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


CPP = g++
CPP_FLAGS = $(GLOBALCCOPTIONS) -D_REENTRANT -g
CPP_INCLUDES = -I. -I../
CPP_DEFINES = 
SOCKETLIBS = 
LINKER = ar cru 
SHLINKER = g++ -shared
LINKER_FLAGS = 
LINKER_ENTRY = 
SOCKETOBJECTS = NameResolver.o INetworkAddress.o InternetAddress.o SocketObject.o # SocketAttribute.o APPLETALKSocket.o ATMPVCSocket.o AX25Socket.o INET6Socket.o INETSocket.o IPXSocket.o NETLINKSocket.o PACKETSocket.o SocketSocket.o SocketObject.o SocketTestDriver.o UNIXSocket.o X25Socket.o

all: ../lib/libSocketObject.a ../lib/libSocketObject.so

../lib/libSocketObject.a: $(SOCKETOBJECTS)
	$(LINKER) ../lib/libSocketObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(SOCKETOBJECTS) $(SOCKETLIBS)

../lib/libSocketObject.so: $(SOCKETOBJECTS)
	$(SHLINKER) -o ../lib/libSocketObject.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(SOCKETOBJECTS) $(SOCKETLIBS)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)

clean:
	-rm -f *.o
	-rm -f ../lib/libSocketObject.a
	-rm -f ../lib/libSocketObject.so
