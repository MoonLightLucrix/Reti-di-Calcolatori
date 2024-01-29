C = gcc
CFLAGS = -std=c2x
OBJECTS = Christmas.o Client.o

all: Christmas Client

Christmas.o: Christmas.c
	$(CC) $(CFLAGS) -c Christmas.c

Client.o: Client.c
	$(CC) $(CFLAGS) -c Client.c

Christmas: Christmas.o
	$(CC) Christmas.o -o Christmas
	rm Christmas.o

Client: Client.o
	$(CC) Client.o -o Client
	rm Client.o

clean:
	rm -f *.o Christmas Client