main: main.o function.o lista.o
	gcc main.o function.o lista.o -o main

main.o: main.c
	gcc -c main.c

function.o: function.c
	gcc -c function.c

lista.o: lista.c
	gcc -c lista.c

clean:
	rm -f main main.o lista.o function.o
