
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(GLOBALCCOPTIONS) $(INCLUDE) -D_REENTRANT
LINKEROPTIONS = -L../../lib -lFactoryObject -lException
FACTORYTESTDRIVEROBJECTS =  FactoryTest.o

.SUFFIXES = .cpp .h .c .o

all: FactoryTest 

run: all
	-. ./test.sh
	-FactoryTest

clean:
	-rm *\.o
	-rm FactoryTest
	
FactoryTest: $(FACTORYTESTDRIVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(FACTORYTESTDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

