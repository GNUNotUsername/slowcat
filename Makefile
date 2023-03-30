CC=gcc
CFLAGS= -Wall -pedantic --std=gnu99 -g

.PHONY: slowcat clean #install
.DEFAULT_GOAL := slowcat

slowcat: slowcat.c
	$(CC) $(CFLAGS) slowcat.c -o slowcat

install:
	cp ./slowcat /usr/local/bin/slowcat

clean:
	rm -f slowcat *.o
