CC = gcc
CFLAGS = -Wall

all: main

main: main.o game.o utils.o
		$(CC) $(CFLAGS) -o main main.o game.o utils.o

main.o: main.c game.h
		$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
		$(CC) $(CFLAGS) -c game.c

utils.o: utils.c game.h
		$(CC) $(CFLAGS) -c utils.c

clean:
		rm -f *.o main
