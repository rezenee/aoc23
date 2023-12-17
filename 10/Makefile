EXE = p1 p2
OBJECTS = p1.o p2.o
CXXFLAGS ?= -g -Wall
AOC_DIR = ../
all: $(EXE)

aoc.o : $(AOC_DIR)aoc.cpp $(AOC_DIR)aoc.h
	$(CXX) $(CXXFLAGS) -c -o $(AOC_DIR)aoc.o $(AOC_DIR)aoc.cpp

p2 : p2.o $(AOC_DIR)aoc.o
	$(CXX) $(CXXFLAGS) -o p2 p2.o $(AOC_DIR)aoc.o

p2.o : p2.cpp
	$(CXX) $(CXXFLAGS) -c -o p2.o p2.cpp

p1 : p1.o $(AOC_DIR)aoc.o
	$(CXX) $(CXXFLAGS) -o p1 p1.o $(AOC_DIR)aoc.o

p1.o : p1.cpp
	$(CXX) $(CXXFLAGS) -c -o p1.o p1.cpp

.PHONY : clean all
clean :
	rm -f $(EXE) $(OBJECTS) $(AOC_DIR)aoc.o
