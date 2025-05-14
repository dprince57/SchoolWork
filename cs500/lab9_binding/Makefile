SHELL = /bin/sh
CFLAGS = -g -Wall -O0 -lm 
#CFLAGS = -Wall -O4 -lm 

all: fasta_driver.o pbm_driver.o binding_region_driver.o combinations.o

fasta_driver.o : fasta.c fasta.h fasta_driver.c
	-gcc $(CFLAGS) fasta.c fasta_driver.c -o fasta_driver.o

pbm_driver.o : pbm.c pbm.h pbm_driver.c
	-gcc $(CFLAGS) pbm.c pbm_driver.c -o pbm_driver.o

combinations.o : combinations.c combinations.h combinations_driver.c
	-gcc $(CFLAGS) combinations.c combinations_driver.c -o combinations.o

binding_region_driver.o : pbm.c pbm.h fasta.c fasta.h binding_region.h binding_region.c binding_region_driver.c all_values.h combinations.h all_values.c combinations.c
	-gcc $(CFLAGS) pbm.c fasta.c binding_region.c all_values.c combinations.c binding_region_driver.c -o binding_region_driver.o

clean:
	rm -f *.o
