default: console

console: console.c src/communication.c src/functions.c platform/include.c
	gcc console.c src/*.c platform/*.c -o console.o

clean:
	-rm -f console.o
	-rm -f console