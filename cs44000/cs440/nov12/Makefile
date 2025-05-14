CC = cc
CFLAGS= -c -g
LDFLAGS= -L/usr/X11/lib
LIBS= -lglut -lGLU -lGL -lX11 -lm

bmw: bmw.o ppm.o
	$(CC) -g $(LDFLAGS) bmw.o ppm.o $(LIBS) -o $@
bmw.o: bmw.c
	$(CC) $(CFLAGS) bmw.c
ppm.o: ppm.c
	$(CC) $(CFLAGS) ppm.c
clean:
	rm -f *.o bmw
