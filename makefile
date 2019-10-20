main: main.o function.o lista.o stack.o
	gcc main.o function.o lista.o stack.o -o main

main.o: main.c
	gcc -c main.c

function.o: function.c
	gcc -c function.c

lista.o: lista.c
	gcc -c lista.c

stack.o: stack.c
	gcc -c stack.c

clean:
	rm -f main main.o lista.o function.o stack.o
