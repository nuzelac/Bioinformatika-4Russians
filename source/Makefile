OBJS = main.o Blok.o Cell.o FourRussians.o
CC = g++
DEBUG = -std=c++11 -g
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

FourRussians.o : FourRussians.cpp FourRussians.h Cell.o Blok.o
	$(CC) $(CFLAGS) FourRussians.cpp

clean:
	rm -f *.o *~ p1
