#########################################################
# makefile

include ../makefile.global


.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

threadobject_OBJECTS = ThreadSuper.o ThreadAttribute.o Mutex.o AutoMutex.o AutoMutexTry.o

all: ../lib/libThreadObject.a ../lib/libThreadObject.so

../lib/libThreadObject.a: $(threadobject_OBJECTS)
	$(LINKER) ../lib/libThreadObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(threadobject_OBJECTS) $(threadobject_LIBS)

../lib/libThreadObject.so: $(threadobject_OBJECTS)
	$(SHLINKER) -o ../lib/libThreadObject.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(threadobject_OBJECTS) $(threadobject_LIBS)

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
	-rm -f ../lib/libThreadObject.a
	-rm -f ../lib/libThreadObject.so

