.DEFAULT_GOAL := all
.PHONY test1 test2 clean

all:	medie_file.o

medie_file.o: medie_file.c
	gcc medie_file.c -o  medie_file.o -lm

test1:  medie_file.o
	echo "Running test1"
	./medie_file.o .
	make clean
	echo "Done"

test2:
	echo "Running test2"
	chmod +x medie_file.sh
	./medie_file.sh .
	echo "Done"

clean:
	rm -f *.o