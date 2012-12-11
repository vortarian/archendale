
include ../../makefile.global

LINKEROPTIONS = -L../../lib -lException
ExceptionTestDriverObjects = ExceptionTestDriver.o

.SUFFIXES = .cpp .h .c .o

all: ExceptionTestDriver

run: all
	-./ExceptionTestDriver

clean:
	-rm *\.o
	-rm ExceptionTestDriver
	
ExceptionTestDriver: $(ExceptionTestDriverObjects) 
	$(CPP) $(CPP_FLAGS) -o $@ $(ExceptionTestDriverObjects)  $(LINKEROPTIONS) 

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

