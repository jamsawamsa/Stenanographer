all: hide unhide

CC = gcc
CFLAGS=-I.
DEPS=structs.h readPpm.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hide: hide.c
	$(CC) -o hide hide.c -I.

unhide: unhide.c
	$(CC) -o unhide unhide.c -lm -I.
