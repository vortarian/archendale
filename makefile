
export GLOBALCCOPTIONS = -d

all: 
	make -C Exception -j
	make -C ThreadObject -j
	make -C String -j
	make -C UnitTest -j

run:
	make -C UnitTest run

clean:
	make -C Exception clean
	make -C String clean
	make -C ThreadObject clean
	make -C UnitTest clean

touch:
	touch ./makefile
	touch ./Exception/makefile
	touch ./String/makefile
	touch ./ThreadObject/makefile

