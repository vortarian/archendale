
OBJECTS 	= SocketObject.o SocketAttribute.o 
CC		= g++
CCOPTIONS	= $(GLOBALCCOPTIONS)
EXE		= SocketTestDriver

$(EXE): $(OBJECTS) $?.o
	$(CC) $(CCOPTIONS) -o $@ $(OBJECTS) $@.o

.cpp.o: $<
	$(CC) $(CCOPTIONS) -c $<

clean: 
	-rm $(OBJECTS) $(EXE)
