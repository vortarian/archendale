
include ../../makefile.global

LINKEROPTIONS = -L../../lib -lIOObject -lException
IOTESTDRIVEROBJECTS =  IOTest.o

.SUFFIXES = .cpp .h .c .o

all: IOTest

run: all
	-./IOTest

clean:
	-rm *\.o
	-rm IOTest
	
IOTest: $(IOTESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(IOTESTDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

