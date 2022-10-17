# -*- MakeFile -*-

assignment: main.o student.o
	gcc main.o student.o -o assignment

main.o: main.c
	gcc -c main.c

student.o: student.c
	gcc -c student.c