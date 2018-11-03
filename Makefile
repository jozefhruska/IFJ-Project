CFLAGS=-std=c99 -Wall -pedantic -g
CC=gcc

demel: parser.c parser.h main.c
	$(CC) $(CFLAGS) parser.c main.c -o demel

hruska: list.c list.h symtable.c symtable.h main.c
	$(CC) $(CFLAGS) symtable.c list.c main.c -o hruska

sedlacek: scaner.c scaner.h main.c
	$(CC) $(CFLAGS) scaner.c main.c -o sedlacek

clean:
	rm demel sedlacek hruska
