#########################################################
# makefile

include ../makefile.global

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y
UTILOBJECTS = SequenceGenerator.o

all: ../lib/libUtilObject.a ../lib/libUtilObject.so

../lib/libUtilObject.a: $(UTILOBJECTS)
	$(LINKER) ../lib/libUtilObject.a $(LINKER_ENTRY) $(LINKER_FLAGS) $(UTILOBJECTS) $(UTILLIBS)

../lib/libUtilObject.so: $(UTILOBJECTS)
	$(SHLINKER) -o ../lib/libUtilObject.so $(LINKER_ENTRY) $(LINKER_FLAGS) $(UTILOBJECTS) $(UTILLIBS)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)

clean:
	-rm -f *.o
	-rm -f ../lib/libUtilObject.a
	-rm -f ../lib/libUtilObject.so
