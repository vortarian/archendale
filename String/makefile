#########################################################
# makefile


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


JAVA = gcj
CC = gcc
CPP = g++
JAVA_FLAGS =      
CC_FLAGS = $(GLOBALCCOPTIONS)    
CPP_FLAGS = $(GLOBALCCOPTIONS)
JAVA_INCLUDES = 
CC_INCLUDES = 
CPP_INCLUDES = -I. -I..
JAVA_DEFINES = 
CC_DEFINES = 
CPP_DEFINES = 
string_LIBS = 
LINKER = ar cru
SHLINKER = g++ -shared
LINKER_FLAGS = 
LINKER_ENTRY = 
string_OBJECTS = String.o

all: ../lib/libString.a ../lib/libString.so

../lib/libString.a: $(string_OBJECTS)
	$(LINKER) ../lib/libString.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(string_OBJECTS) $(string_LIBS)

../lib/libString.so: $(string_OBJECTS)
	$(SHLINKER) -o ../lib/libString.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(string_OBJECTS) $(string_LIBS)

.java.o:
	$(JAVA) -c $< $(JAVA_FLAGS) $(JAVA_DEFINES) $(JAVA_INCLUDES)
.class:
	$(JAVA) -c $< $(JAVA_FLAGS) $(JAVA_DEFINES) $(JAVA_INCLUDES)

.c.o:
	$(CC) -c $< $(CC_FLAGS) $(CC_DEFINES) $(CC_INCLUDES)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)

clean:
	-rm -f *.o
	-rm -f ../lib/libString.a
	-rm -f ../lib/libString.so

