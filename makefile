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
	main -f1 table_R_500.txt -s1 500 -f2 table_S_500.txt -s2 500

run2:
	main -f1 table_R_10.000.txt -s1 10000 -f2 table_S_10.000.txt -s2 10000

run3:
	main -f1 table_R_100.000.txt -s1 100000 -f2 table_S_100.000.txt -s2 100000
