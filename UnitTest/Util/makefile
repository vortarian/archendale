
include ../../makefile.global

REFTESTDRIVEROBJECTS = ReferenceCounter.o
REFLINKEROPTIONS = -L../../lib -lUtilObject -lException -lIOObject -lFactoryObject

SEQUENCETESTDRIVEROBJECTS =  SequenceTest.o
SEQUENCELINKEROPTIONS = -L../../lib -lUtilObject -lException -lIOObject -lFactoryObject

.SUFFIXES = .cpp .h .c .o

all: SequenceTest ReferenceCounterTest

run: all
	-./SequenceTest
	-./ReferenceCounterTest

clean:
	-rm *\.o
	-rm SequenceTest ReferenceCounterTest
	
SequenceTest: $(SEQUENCETESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(SEQUENCETESTDRIVEROBJECTS) $(SEQUENCELINKEROPTIONS)

ReferenceCounterTest: $(REFTESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(REFTESTDRIVEROBJECTS) $(REFLINKEROPTIONS)


.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<
