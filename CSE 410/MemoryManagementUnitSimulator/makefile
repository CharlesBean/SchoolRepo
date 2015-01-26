CPPFLAGS=-std=c++11 -g -O3 -Wall
EXECUTABLE=PROG05

PROG05: main.o
	g++ $(CPPFLAGS) main.o -o $(EXECUTABLE)

main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp

PageTable.o: PageTable.h
	g++ $(CPPFLAGS) -c PageTable.h

PageTableEntry.o: PageTableEntry.h
	g++ $(CPPFLAGS) -c PageTableEntry.h

FrameTable.o: FrameTable.h
	g++ $(CPPFLAGS) -c FrameTable.h

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)

