#########################################################
# Makefile auto generated by Cygnus Source Navigator.
# Target: exception Date: Mar 17 2001 Time: 02:48:12 PM
#


include ../makefile.global


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


exception_OBJECTS = exception.o

all: ../lib/libException.a ../lib/libException.so

../lib/libException.a: $(exception_OBJECTS)
	$(LINKER) ../lib/libException.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(exception_OBJECTS) $(exception_LIBS)

../lib/libException.so: $(exception_OBJECTS)
	$(SHLINKER) -o ../lib/libException.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(exception_OBJECTS) $(exception_LIBS)


.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)


clean:
	-rm -f *.o
	-rm -f ../lib/libException.a
	-rm -f ../lib/libException.so

