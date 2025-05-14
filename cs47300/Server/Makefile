
CC = gcc
CFLAGS = -g -lcrypt

server: main.o net.o app.o commands.o
	$(CC) $(CFLAGS) -o server main.o net.o app.o commands.o
main.o: main.c server.h
	$(CC) $(CFLAGS) -c main.c
net.o: net.c server.h
	$(CC) $(CFLAGS) -c net.c
app.o: app.c server.h
	$(CC) $(CFLAGS) -c app.c
commands.o: commands.c server.h
	$(CC) $(CFLAGS) -c commands.c
clean:
	rm *.o server
