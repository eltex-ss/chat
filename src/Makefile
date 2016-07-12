objects = server.o client.o list.o

CFLAGS = -Wall -pedantic -ansi -g

targets = server client

all : $(targets) reloc

server : server.o list.o
		$(CC) -o $@ $^

client : client.o
		$(CC) -o $@ $<

list.o : list.h
server.o : list.h
server.o : common.h
client.o : common.h
$(objects) : %.o : %.c
		$(CC) -c $(CFLAGS) $<

.PHONY : clean reloc

reloc :
		mkdir -p ../build
		mv $(targets) ../build

clean :
		-rm -r $(objects) ../build
