
export GLOBALCCOPTIONS = -d

all: lib writeclass 
	make -C UnitTest -j

lib:
	make -C Exception -j
	make -C ThreadObject -j
	make -C String -j

run:
	make -C UnitTest run

clean:
	-rm -f *.o
	make -C Exception clean
	make -C String clean
	make -C ThreadObject clean
	make -C UnitTest clean

touch:
	touch ./makefile
	touch ./Exception/makefile
	touch ./String/makefile
	touch ./ThreadObject/makefile

.SUFFIXES: .cc .class .java .cxx .C .cpp .o .c .l .y

CPP = g++
CPP_FLAGS = $(GLOBALCCOPTIONS) -D_REENTRANT
CPP_INCLUDES = -I. -I../
CPP_DEFINES = 

 writeclass:  writeclass.o 
	$(CPP) -o  writeclass  writeclass.o lib/libString.so lib/libException.so
	
.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(CPP_DEFINES) $(CPP_INCLUDES)
