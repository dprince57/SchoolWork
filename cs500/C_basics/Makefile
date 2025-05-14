SHELL = /bin/sh
CFLAGS = -g -Wall -O0 -lm 
#CFLAGS = -Wall -O4 -lm 
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(OBJS)

%.o : %.c
	-gcc $(CFLAGS) $< -o $@

clean:
	rm -f *.o
