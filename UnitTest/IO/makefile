
include ../../makefile.global

IOLINKEROPTIONS = -L../../lib -lIOObject -lException
IENTRYLINKEROPTIONS = -L../../lib -lIOObject -lException -lFactoryObject
IOTESTDRIVEROBJECTS =  IOTest.o
IENTRYTESTDRIVEROBJECTS =  IEntryTest.o

.SUFFIXES = .cpp .h .c .o

all: IOTest IEntryTest

run: all
	-./IOTest
	-./IEntryTest

clean:
	-rm *\.o
	-rm IOTest
	-rm IEntryTest
	
IOTest: $(IOTESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(IOTESTDRIVEROBJECTS)  $(IOLINKEROPTIONS)

IEntryTest: $(IENTRYTESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(IENTRYTESTDRIVEROBJECTS)  $(IENTRYLINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<
