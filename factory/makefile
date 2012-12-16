#########################################################
# makefile

include ../makefile.global

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

FACTORYOBJECTS = factory.o

all: ../lib/libFactoryObject.a ../lib/libFactoryObject.so

../lib/libFactoryObject.a: $(FACTORYOBJECTS)
	$(LINKER) ../lib/libFactoryObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(FACTORYOBJECTS) $(FACTORYLIBS)

../lib/libFactoryObject.so: $(FACTORYOBJECTS)
	$(SHLINKER) -o ../lib/libFactoryObject.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(FACTORYOBJECTS) $(FACTORYLIBS)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)

clean:
	-rm -f *.o
	-rm -f ../lib/libFactoryObject.a
	-rm -f ../lib/libFactoryObject.so
