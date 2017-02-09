default: console

console: console.c src/communication.c src/platform.c
	gcc -Wall console.c src/*.c -o console.o

clean:
	-rm -f console.o
	-rm -f console