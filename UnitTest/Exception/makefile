
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(INCLUDE) -D_REENTRANT
LINKEROPTIONS = -L../../lib -lException -lString
ExceptionTestDriverObjects = ExceptionTestDriver.o

.SUFFIXES = .cpp .h .c .o

all: ExceptionTestDriver

run: all
	./ThreadSuperTestDriver

clean:
	rm *\.o
	rm ExceptionTestDriver
	
ExceptionTestDriver: $(ExceptionTestDriverObjects) 
	$(CC) $(CCOPTIONS) -o $@ $(ExceptionTestDriverObjects)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

