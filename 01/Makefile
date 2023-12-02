EXE = 01_p2
OBJECTS = 01_p2.o
CFLAGS = -g
01_p2 : 01_p2.o
	g++ -o $(EXE) $(OBJECTS) $(CFLAGS)

01_p2.o : 01_p2.cpp
	g++ $(CFLAGS) -c -o $(OBJECTS) 01_p2.cpp

.PHONY : clean
clean :
	rm -f $(EXE) $(OBJECTS)
