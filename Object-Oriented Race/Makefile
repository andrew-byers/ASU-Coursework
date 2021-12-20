OBJS = byers_andrew_main.o byers_race.o byers_racer.o byers_segments.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o exe

byers_andrew_main.o : byers_race.o byers_racer.o byers_segments.o
	$(CC) $(CFLAGS) byers_andrew_main.cpp

byers_race.o : byers_race.h byers_race.cpp
	$(CC) $(CFLAGS) byers_race.cpp

byers_racer.o : byers_racer.h byers_racer.cpp
	$(CC) $(CFLAGS) byers_racer.cpp

byers_segments.o : byers_segments.h byers_segments.cpp
	$(CC) $(CFLAGS) byers_segments.cpp

clean:
	rm *.o exe -v

