default: console

console: console.c src/protocol.c src/protocol_platform_console.c
	gcc -Wall -o console.o console.c src/protocol.c src/protocol_platform_console.c

wiringpi: console.c src/protocol.c src/protocol_platform_wiringpi.c
	gcc -Wall -o console.o console.c src/protocol.c src/protocol_platform_wiringpi.c -lwiringPi

clean:
	-rm -f console.o
	-rm -f console
