CPPFLAGS=-std=c++11 -g -O3 -Wall
EXECUTABLE=prog

all: Main.o HashFunc.o
	g++ $(CPPFLAGS) Main.o HashFunc.o -o $(EXECUTABLE)

Hash.o: HashFunc.cpp HashSet.h
	g++ $(CPPFLAGS) -c HashFunc.cpp

Main.o: Main.cpp
	g++ $(CPPFLAGS) -c Main.cpp

clean: 
	rm -f *.o
	rm -f $(EXECUTABLE)