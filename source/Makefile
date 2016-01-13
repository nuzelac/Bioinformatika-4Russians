OBJS = main.o Blok.o Cell.o FourRussians.o Hash.o
CC = g++
DEBUG = -std=c++11
CFLAGS = -c $(DEBUG) -O2 -pthread
LFLAGS = -Wall $(DEBUG) -pthread

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

main.o : main.cpp FourRussians.o
	$(CC) $(CFLAGS) main.cpp

Blok.o : Blok.cpp Blok.h
	$(CC) $(CFLAGS) Blok.cpp

Cell.o : Cell.cpp Cell.h
	$(CC) $(CFLAGS) Cell.cpp

FourRussians.o : FourRussians.cpp Cell.o Blok.o Hash.o
	$(CC) $(CFLAGS) FourRussians.cpp

Hash.o : Hash.cpp
	$(CC) $(CFLAGS) Hash.cpp

clean:
	rm -f *.o *~ p1
