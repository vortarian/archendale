
CC = g++
INCLUDE = -I../../
CCOPTIONS = $(INCLUDE) -D_REENTRANT
#THREADSUPERTESTDRIVERLIBS = /home/vortex/project/lib/libException.a /home/vortex/project/lib/libString.a /home/vortex/project/lib/libThreadObject.a
LINKEROPTIONS = -L/home/vortex/project/lib -lpthread -lException -lString -lThreadObject  $(THREADSUPERTESTDRIVERLIBS) $(THREADSUPERTESTDRIVERLIBS)
THREADSUPERTESTDRIVEROBJECTS = ThreadSuperTestDriver.o

.SUFFIXES = .cpp .h .c .o

all: ThreadSuperTestDriver

clean:
	rm *\.o
	rm ThreadSuperTestDriver
	
ThreadSuperTestDriver: $(THREADSUPERTESTDRIVEROBJECTS) 
	$(CC) $(CCOPTIONS) -o $@ $(THREADSUPERTESTDRIVEROBJECTS)  $(LINKEROPTIONS)


#../../ThreadObject/Mutex.o  ../../ThreadObject/ThreadAttribute.o  ../../ThreadObject/ThreadSuper.o ../../Exception/Exception.o ../../String/String.o


.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

