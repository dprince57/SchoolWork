
CC = gcc
CFLAGS = -g

server: main.o net.o app.o
	$(CC) $(CFLAGS) -o server main.o net.o app.o

main.o: main.c server.h
	$(CC) $(CFLAGS) -c main.c
net.o: net.c server.h
	$(CC) $(CFLAGS) -c net.c
app.o: app.c server.h
	$(CC) $(CFLAGS) -c app.c
