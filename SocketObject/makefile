#########################################################
# makefile


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


CPP = g++
CPP_FLAGS = $(GLOBALCCOPTIONS) -D_REENTRANT
CPP_INCLUDES = -I. -I../
CPP_DEFINES = 
SOCKETLIBS = 
LINKER = ar cru 
SHLINKER = g++ -shared
LINKER_FLAGS = 
LINKER_ENTRY = 
SOCKETOBJECTS = SocketObject.o SocketAttribute.o APPLETALKAttribute.o ATMPVCAttribute.o AX25Attribute.o INET6Attribute.o INETAttribute.o IPXAttribute.o NETLINKAttribute.o PACKETAttribute.o SocketAttribute.o SocketObject.o SocketTestDriver.o UNIXAttribute.o X25Attribute.o

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
