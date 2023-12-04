EXE = p1 p2
OBJECTS = p1.o p2.o
CXXFLAGS ?= -g -Wall
all: $(EXE)

p2 : p2.o
	$(CXX) -o p2 p2.o $(CXXFLAGS)

p2.o : p2.cpp
	$(CXX) $(CXXFLAGS) -c -o p2.o p2.cpp

p1 : p1.o
	$(CXX) -o p1 p1.o $(CXXFLAGS)

p1.o : p1.cpp
	$(CXX) $(CXXFLAGS) -c -o p1.o p1.cpp

.PHONY : clean all
clean :
	rm -f $(EXE) $(OBJECTS)
