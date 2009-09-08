all: compile run

compile: clean
	gcc -Wall -pthread -o bin/carparker src/*.c

run:
	bin/carparker

clean:
	rm -f bin/*