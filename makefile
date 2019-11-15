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

run1:
	./main -f1 table_R_10.000 -s1 10000 -f2 table_S_10.000 -s2 10000

run2:
	./main -f1 table_R_100.000 -s1 100000 -f2 table_S_100.000 -s2 100000

run3:
	./main -f1 table_R_1.000.000 -s1 1000000 -f2 table_S_1.000.000 -s2 1000000
