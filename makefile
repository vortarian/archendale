
include ./makefile.global

all: libraries # writeclass 
	make -C UnitTest -j

libraries: 
	make -C Exception -j
	make -C ThreadObject -j
	make -C String -j
	make -C CGI -j
	make -C IO -j
	make -C Factory -j
	make -C SocketObject -j

run:
	make -C UnitTest run

clean:
	-rm -f *.o
	-rm writeclass
	make -C Exception clean -j 
	make -C String clean -j 
	make -C ThreadObject clean -j 
	make -C IO clean -j 
	make -C CGI clean -j 
	make -C Factory clean -j 
	make -C UnitTest clean -j 
	make -C SocketObject clean -j 

touch:
	touch ./makefile
	touch ./Exception/makefile
	touch ./String/makefile
	touch ./ThreadObject/makefile
	touch ./CGI/makefile
	touch ./Factory/makefile
	touch ./SocketObject/makefile

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

writeclass:  writeclass.o libraries  
	$(CPP) -o  writeclass writeclass.o -L./lib -lString -lException
	
.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)
