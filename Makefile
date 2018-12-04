CFLAGS=-std=c99 -Wall -pedantic -g
CC=gcc

make:
	$(CC) $(CFLAGS) error_handler.c parser_syntax_rules.c generator.c generator_str.c parser_syntax_prec_analysis.c parser.c token.c scanner.c pokusne_odevzdani.c semantic.c symtable.c list.c -o compilator

demel: main.c
	$(CC) $(CFLAGS) error_handler.c generator.c generator_str.c parser_syntax_rules.c parser_syntax_prec_analysis.c parser.c token.c scanner.c main.c semantic.c symtable.c list.c -o demel

hruska: list.c list.h generator.h generator.c generator_str.h generator_str.c error_handler.c error_handler.h main.c
	$(CC) $(CFLAGS) list.c generator.c generator_str.c error_handler.c main.c -o hruska

sedlacek: main.c
	$(CC) $(CFLAGS) scanner.c token.c list.c main.c error_handler.c -o sedlacek

sedlacek_gen: main.c
	$(CC) $(CFLAGS) scanner.c token.c list.c generator.c generator_str.c error_handler.c main.c -o sedlacek_gen

buchta: semantic.c error_handler.c list.c symtable.c tests/semantic.c
	$(CC) $(CFLAGS) tests/semantic.c semantic.c error_handler.c list.c symtable.c -o buchta -DERROR_NOT_EXIT

clean:
	rm demel sedlacek hruska compilator sedlacek_gen
