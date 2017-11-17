main:	main.o	stages.o
	gcc main.o stages.o -o exec
	./exec

main.o:	main.c
	gcc -c main.c

stages.o:	stages.c
	gcc -c stages.c

clean:
	rm *.o
