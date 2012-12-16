#########################################################
# makefile

include ../makefile.global

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

SOCKETOBJECTS = name_resolver.o inetwork_address.o internet_address.o socket.o inet.o handle.o server.o # socketattribute.o appletalksocket.o atmpvcsocket.o ax25socket.o inet6socket.o inetsocket.o ipxsocket.o netlinksocket.o packetsocket.o socketsocket.o socketobject.o sockettestdriver.o unixsocket.o x25socket.o

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
