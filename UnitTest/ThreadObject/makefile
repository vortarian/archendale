

include ../../makefile.global

LINKEROPTIONS = -L../../lib -lpthread -lException -lThreadObject
THREADSUPERTESTDRIVEROBJECTS =  DetachedThreadRunner.o ThreadSuperTestDriver.o ThreadCounter.o

.SUFFIXES = .cpp .h .c .o

all: ThreadSuperTestDriver

run: all
	-./ThreadSuperTestDriver

clean:
	-rm *\.o
	-rm ThreadSuperTestDriver
	
ThreadSuperTestDriver: $(THREADSUPERTESTDRIVEROBJECTS) 
	$(CPP) $(CPP_FLAGS) -o $@ $(THREADSUPERTESTDRIVEROBJECTS) $(LINKEROPTIONS) 

.cpp.o:	$<
	$(CPP) $(CPP_FLAGS) -c $<

