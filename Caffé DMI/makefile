CC = gcc
CFLAGS = -std=c2x
OBJECTS = bin/Server.o bin/Client.o

all: create_folder bin/Server bin/Client

create_folder:
	mkdir -p bin

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/Server: bin/Server.o
	$(CC) $< -o $@
	rm -f $<

bin/Client: bin/Client.o
	$(CC) $< -o $@
	rm -f $<

clean:
	rm -f bin/*.o bin/Server bin/Client
	rmdir bin
