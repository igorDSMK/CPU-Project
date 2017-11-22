main:	main.o	stages.o
	gcc main.o stages.o -o exec
	./exec

main.o:	main.c
	gcc -std=c99 -Wall -Werror -c main.c

stages.o:	stages.c
	gcc -std=c99 -Wall -Werror -c stages.c

clean:
	rm *.o
