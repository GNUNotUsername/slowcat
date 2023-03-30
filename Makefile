CC=gcc
CFLAGS= -Wall -pedantic --std=gnu99 -g

.PHONY: slowcat clean #install
.DEFAULT_GOAL := slowcat

slowcat: slowcat.c
	$(CC) $(CFLAGS) slowcat.c -o slowcat

#install:
#	ln -sf ./slowcat /usr/bin/slowcat

clean:
	rm -f slowcat *.o
