
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(GLOBALCCOPTIONS) $(INCLUDE) -D_REENTRANT
LINKEROPTIONS = -L../../lib -lCGIObject -lException
CGITESTDRIVEROBJECTS =  CGITest.o

.SUFFIXES = .cpp .h .c .o

all: CGITest

run: all
	-. ./test.sh

clean:
	-rm *\.o
	-rm CGITest
	
CGITest: $(CGITESTDRIVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(CGITESTDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

