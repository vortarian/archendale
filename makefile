
include ./makefile.global

all: libraries # writeclass 
	make -C test -j

libraries: 
	make -C exception -j
	make -C thread -j
	make -C string -j
	make -C cgi -j
	make -C io -j
	make -C factory -j
	make -C socket -j
	make -C util -j

run:
	make -C test run

clean:
	-rm -f *.o
	-rm writeclass
	make -C exception clean -j 
	make -C string clean -j 
	make -C thread clean -j 
	make -C io clean -j 
	make -C cgi clean -j 
	make -C factory clean -j 
	make -C test clean -j 
	make -C util clean -j 
	make -C socket clean -j 

touch:
	touch ./makefile
	touch ./exception/makefile
	touch ./io/makefile
	touch ./util/makefile
	touch ./string/makefile
	touch ./thread/makefile
	touch ./cgi/makefile
	touch ./factory/makefile
	touch ./socket/makefile

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

writeclass:  writeclass.o libraries  
	$(CPP) -o  writeclass writeclass.o -L./lib -lString -lException
	
.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)
