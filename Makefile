CFLAGS=-std=c99 -Wall -pedantic -g
CC=gcc

TARGET=compilator
TARGET_DEBUG=compilator_debug

SOURCES=$(filter-out main_debug.c, $(wildcard *.c))
SOURCES_DEBUG=$(filter-out main.c, $(wildcard *.c))
OBJECTS=$(SOURCES:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

debug: $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES_DEBUG) -o $(TARGET_DEBUG)

clean:
	rm -r *.o $(TARGET) $(TARGET_DEBUG)