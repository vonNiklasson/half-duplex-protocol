default: main

main: main.c src/comm.c src/functions.c src/convert.c src/global.c gpio/gpio.c
	gcc main.c src/comm.c src/functions.c src/convert.c src/global.c gpio/gpio.c -o main.o

clean:
	-rm -f main.o
	-rm -f main