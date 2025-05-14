SHELL = /bin/sh
CFLAGS = -g -Wall -O0 -lm 
#CFLAGS = -Wall -O4 -lm 

all: fasta_driver.o

fasta_driver.o : fasta.c fasta.h fasta_driver.c
	-gcc $(CFLAGS) fasta.c fasta_driver.c -o fasta_driver.o

clean:
	rm -f *.o
