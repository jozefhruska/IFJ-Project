CFLAGS=-std=c99 -Wall -pedantic -g
BIN=project
CC=gcc
RM=rm -f

ALL: str.o symtable.o error_handler.o ilist.o scaner.o parser.o interpret.o main.o
	$(CC) $(CFLAGS) -o $(BIN) str.o symtable.o error_handler.o ilist.o scaner.o parser.o interpret.o main.o

clean:
	$(RM) *.o $(BIN)
