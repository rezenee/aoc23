EXE = 01
OBJECTS = 01.o
CFLAGS = -g
01 : 01.o
	g++ -o $(EXE) $(OBJECTS) $(CFLAGS)

01.o : 01.cpp
	g++ $(CFLAGS) -c -o $(OBJECTS) 01.cpp

.PHONY : clean
clean :
	rm -f $(EXE) $(OBJECTS)
