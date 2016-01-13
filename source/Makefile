OBJS = main.o Blok.o Cell.o
CC = g++
DEBUG = -std=c++11 -g
CFLAGS = -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

main.o : main.cpp Blok.h
	$(CC) $(CFLAGS) main.cpp

Blok.o : Blok.cpp Cell.h fourRussians.h
	$(CC) $(CFLAGS) Blok.cpp

Cell.o : Cell.cpp Cell.h 
	$(CC) $(CFLAGS) Cell.cpp

clean:
	rm -f *.o *~ p1
