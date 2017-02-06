default: main

main: main.c comm.c src/functions.c
	gcc main.c comm.c src/functions.c -o main.o

clean:
	-rm -f main.o
	-rm -f main