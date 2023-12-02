EXE = p1 p2
OBJECTS = p1.o p2.o
CFLAGS = -g
all: p1 p2

p2 : p2.o
	g++ -o p2 p2.o $(CFLAGS)

p2.o : p2.cpp
	g++ $(CFLAGS) -c -o p2.o p2.cpp

p1 : p1.o
	g++ -o p1 p1.o $(CFLAGS)

p1.o : p1.cpp
	g++ $(CFLAGS) -c -o p1.o p1.cpp

.PHONY : clean
clean :
	rm -f $(EXE) $(OBJECTS)
