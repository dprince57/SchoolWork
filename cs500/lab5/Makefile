SHELL = /bin/sh
CFLAGS = -g -Wall -O0 -lm 
#CFLAGS = -Wall -O4 -lm 

all: pbm_driver.o

pbm_driver.o : pbm.c pbm.h pbm_driver.c
	-gcc $(CFLAGS) pbm.c pbm_driver.c -o pbm_driver.o

clean:
	rm -f *.o
