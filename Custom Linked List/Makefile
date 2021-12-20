OBJS = byers_andrew_assn4.o byers_list.o byers_node.o byers_zombie.o termcolor.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o exe

byers_andrew_assn4.o : byers_list.o byers_node.o byers_zombie.o termcolor.o
	$(CC) $(CFLAGS) byers_andrew_assn4.cpp

byers_list.o : byers_list.h

byers_node.o : byers_node.h

byers_zombie.o : byers_zombie.h byers_zombie.cpp termcolor.hpp
	$(CC) $(CFLAGS) byers_zombie.cpp

termcolor.o : termcolor.hpp

clean:
	rm *.o exe -v
