CFLAGS=-std=c99 -Wall -pedantic -g
CC=gcc

demel: main.c
	$(CC) $(CFLAGS) error_handler.c parser_syntax_rules.c parser_syntax_prec_analysis.c parser.c token.c scanner.c main.c -o demel

hruska: list.c list.h symtable.c symtable.h error_handler.c error_handler.h main.c
	$(CC) $(CFLAGS) symtable.c list.c error_handler.c main.c -o hruska

sedlacek: scanner.c scanner.h token.c token.h main.c
	$(CC) $(CFLAGS) scanner.c main.c token.c -o sedlacek

clean:
	rm demel sedlacek hruska