
CC = g++
INCLUDE = -I../..
CCOPTIONS = $(GLOBALCCOPTIONS) $(INCLUDE)
LINKEROPTIONS = -L../../lib -lException
ExceptionTestDriverObjects = ExceptionTestDriver.o

.SUFFIXES = .cpp .h .c .o

all: ExceptionTestDriver

run: all
	-./ExceptionTestDriver

clean:
	-rm *\.o
	-rm ExceptionTestDriver
	
ExceptionTestDriver: $(ExceptionTestDriverObjects) 
	$(CC) $(CCOPTIONS) -o $@ $(ExceptionTestDriverObjects)  $(LINKEROPTIONS)

.cpp.o:	$<
	$(CC) $(CCOPTIONS) -c $<

