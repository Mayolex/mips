all:parser.o moduletp4.o main.o
	gcc -o exe moduletp4.o parser.o main.o -lm
	rm *.o

parser.o:moduletp4.h parser.h
	gcc -c parser.c

moduletp4.o:
	gcc -c moduletp4.c

main.o: moduletp4.h parser.h
	gcc -c main.c

clean:
	rm -rf *.o