
include ../../makefile.global

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
	$(CPP) $(CPP_FLAGS) -o $@ $(CGITESTDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

