
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(GLOBALCCOPTIONS) $(INCLUDE) -D_REENTRANT
LINKEROPTIONS = -L../../lib -lpthread -lException -lString -lThreadObject
THREADSUPERTESTDRIVEROBJECTS = ThreadSuperTestDriver.o

.SUFFIXES = .cpp .h .c .o

all: ThreadSuperTestDriver

run: all
	-./ThreadSuperTestDriver

clean:
	-rm *\.o
	-rm ThreadSuperTestDriver
	
ThreadSuperTestDriver: $(THREADSUPERTESTDRIVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(THREADSUPERTESTDRIVEROBJECTS)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

