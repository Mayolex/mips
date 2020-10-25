all:parser.o moduletp4.o
	gcc -o exe moduletp4.o parser.o -lm
	rm *.o

parser.o:moduletp4.h
	gcc -c parser.c
moduletp4.o:
	gcc -c moduletp4.c

clean:
	rm -rf *.o