default: main

main: main.c src/comm.c src/functions.c src/convert.c src/global.c
	gcc main.c src/comm.c src/functions.c src/convert.c src/global.c -o main.o


custom: main.c src/comm.c src/functions.c src/convert.c src/global.c custom/custom.c
	gcc main.c src/comm.c src/functions.c src/convert.c src/global.c custom/custom.c -o main.o

clean:
	-rm -f main.o
	-rm -f main