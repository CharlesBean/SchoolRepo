CPPFLAGS = -std=c++11 -g -O3

PROG4: main.o
	g++ main.o -o PROG4

main.o: main.cpp handler.h memoryBlock.h buddySystem.h
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm *.o -f
