CC=gcc
CFLAGS= -O2 -std=c99 -Wall -pedantic

all: main

main: main.c error_handler.c error_handler.h
	$(CC) $(CFLAGS) main.c error_handler.c -o main.run

clean:
	rm -r main.run build.zip

zip: *.h *.c Makefile
	zip build.zip *.h *.c Makefile -q