SHELL = /bin/sh
CFLAGS = -g -Wall -O4

all: bst_driver.o

bst_driver.o: bst_driver.c bst.c bst.h
	-gcc $(CFLAGS) bst.c bst_driver.c -o bst_driver.o

clean:
	rm -f *.o
