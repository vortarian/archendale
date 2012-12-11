#########################################################
# makefile

include ../makefile.global

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y


IOOBJECTS 	= ITDF.o OTDF.o IEntry.o

all: ../lib/libIOObject.a ../lib/libIOObject.so

../lib/libIOObject.a: $(IOOBJECTS)
	$(LINKER) ../lib/libIOObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(IOOBJECTS) $(IOLIBS)

../lib/libIOObject.so: $(IOOBJECTS)
	$(SHLINKER) -o ../lib/libIOObject.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(IOOBJECTS) $(IOLIBS)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)

clean:
	-rm -f *.o
	-rm -f ../lib/libIOObject.a
	-rm -f ../lib/libIOObject.so
