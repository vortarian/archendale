
all:
	make -C ThreadObject -j
	make -C SocketObject -j
	make -C Exception -j
	make -C CGI -j
	make -C IO -j
	make -C Factory -j

run:
	make -C ThreadObject run
	make -C Exception run
	make -C CGI run
	make -C SocketObject run
	make -C IO run
	make -C Factory run


clean:
	make -C ThreadObject clean
	make -C Exception clean
	make -C CGI clean
	make -C SocketObject -j clean
	make -C IO -j clean
	make -C Factory -j clean
