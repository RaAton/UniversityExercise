.PHONY: all test1 test2 test3 clean
 
CC = gcc
CFLAGS = -g -Wall -I.
LDLIBS = -lpthread -lm

all: compitino

compitino: compitino.c unboundedqueue.c
	$(CC) $(CFLAGS) -o compitino compitino.c unboundedqueue.c $(LDLIBS)

test1: compitino
	./compitino 1 .
	make clean

test2: compitino
	./compitino 5 .
	make clean

test3: compitino
	valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./compitino 5 .
	make clean

clean:
	rm -f compitino
