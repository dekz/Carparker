CC=gcc
CFLAGS=-Wall -pthread -pedantic -std=gnu99
COMMAND=$(CC) $(CFLAGS)

SRC=src/*.c
BIN=bin/carparker

all: compile run

compile: clean
	$(COMMAND) -o $(BIN) $(SRC)

run:
	$(BIN)

clean:
	rm -f bin/*