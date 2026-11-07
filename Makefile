CC = gcc
CFLAGS = -std=gnu11 -Wall -Werror -g

all: readf

readf: readf.c
	$(CC) $(CFLAGS) readf.c -o readf

.PHONY: clean

clean:
	rm -f readf *.dSYM