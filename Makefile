default: console

console: console.c src/protocol.c src/protocol_platform_console.c
	gcc -Wall console.c src/protocol.c src/protocol_platform_console.c -o console.o

wiringpi: console.c src/protocol.c src/protocol_platform_wiringpi.c
	gcc -Wall console.c src/protocol.c src/protocol_platform_wiringpi.c -lwiringPi -o console.o

clean:
	-rm -f console.o
	-rm -f console
