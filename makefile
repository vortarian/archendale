
all: Exception ThreadObject String 

clean:
	make -C Exception clean
	make -C String clean
	make -C ThreadObject clean

touch:
	touch ./Exception/makefile
	touch ./String/makefile
	touch ./ThreadObject/makefile
	
Exception:
	make -C Exception -j

ThreadObject:
	make -C ThreadObject -j

String:
	make -C String -j
