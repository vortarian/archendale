
export GLOBALCCOPTIONS = -d

all: libraries writeclass 
	make -C UnitTest -j

libraries: 
	make -C Exception -j
	make -C ThreadObject -j
	make -C String -j
	make -C CGI -j
	make -C SocketObject -j

run:
	make -C UnitTest run

clean:
	-rm -f *.o
	make -C Exception clean
	make -C String clean
	make -C ThreadObject clean
	make -C CGI clean
	make -C UnitTest clean
	make -C SocketObject clean

touch:
	touch ./makefile
	touch ./Exception/makefile
	touch ./String/makefile
	touch ./ThreadObject/makefile
	touch ./CGI/makefile
	touch ./SocketObject/makefile

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

CPP = g++
CPP_FLAGS = $(GLOBALCCOPTIONS) -D_REENTRANT
CPP_INCLUDES = -I. -I../
CPP_DEFINES = 

writeclass:  writeclass.o libraries  
	$(CPP) -o  writeclass  writeclass.o -L./lib -lString -lException
	
.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)
