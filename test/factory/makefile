
include ../../makefile.global

LINKEROPTIONS = -L../../lib -lFactoryObject -lException
FACTORYTESTDRIVEROBJECTS =  FactoryTest.o

.SUFFIXES = .cpp .h .c .o

all: FactoryTest 

run: all
	-./FactoryTest

clean:
	-rm *\.o
	-rm FactoryTest
	
FactoryTest: $(FACTORYTESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(FACTORYTESTDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

