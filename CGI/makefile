#########################################################
# makefile


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


CPP = g++
CPP_FLAGS = $(GLOBALCCOPTIONS) -D_REENTRANT -g
CPP_INCLUDES = -I. -I../
CPP_DEFINES = 
CGILIBS = 
LINKER = ar cru 
SHLINKER = g++ -shared
LINKER_FLAGS = 
LINKER_ENTRY = 
CGIOBJECTS = CGI.o

all: ../lib/libCGIObject.a ../lib/libCGIObject.so

../lib/libCGIObject.a: $(CGIOBJECTS)
	$(LINKER) ../lib/libCGIObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(CGIOBJECTS) $(CGILIBS)

../lib/libCGIObject.so: $(CGIOBJECTS)
	$(SHLINKER) -o ../lib/libCGIObject.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(CGIOBJECTS) $(CGILIBS)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)

clean:
	-rm -f *.o
	-rm -f ../lib/libCGIObject.a
	-rm -f ../lib/libCGIObject.so
