
all:
	make -C thread -j
	make -C socket -j
	make -C exception -j
	make -C cgi -j
	make -C io -j
	make -C factory -j
	make -C util -j

run:
	make -C thread run
	make -C exception run
	make -C cgi run
	make -C socket run
	make -C io run
	make -C factory run
	make -C util run


clean:
	make -C thread clean
	make -C exception clean
	make -C cgi clean
	make -C socket -j clean
	make -C io -j clean
	make -C factory -j clean
	make -C util -j clean
