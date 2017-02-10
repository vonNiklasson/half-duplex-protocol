default: console

console: console.c src/protocol.c src/protocol_platform.c
	gcc -Wall console.c src/*.c -o console.o

clean:
	-rm -f console.o
	-rm -f console