#########################################################
# makefile


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


JAVA = gcj
CC = gcc
CPP = g++
JAVA_FLAGS =      
CC_FLAGS =      
CPP_FLAGS = $(GLOBALCCOPTIONS) -D_REENTRANT
JAVA_INCLUDES = 
CC_INCLUDES = 
CPP_INCLUDES = -I. -I../
JAVA_DEFINES = 
CC_DEFINES = 
CPP_DEFINES = 
threadobject_LIBS = 
LINKER = ar
LINKER_FLAGS = 
LINKER_ENTRY = 
threadobject_OBJECTS = ThreadSuper.o ThreadAttribute.o Mutex.o 

all: ../lib/libThreadObject.a

../lib/libThreadObject.a: $(threadobject_OBJECTS)
	$(LINKER) cru ../lib/libThreadObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(threadobject_OBJECTS) $(threadobject_LIBS)

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
	rm -f ../lib/libThreadObject.a

