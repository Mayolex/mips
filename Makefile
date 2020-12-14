all: memory.o main.o parser.o moduletp4.o interpreteur.o instructions.o 
	gcc -o exe moduletp4.o parser.o main.o memory.o instructions.o interpreteur.o -lm
	rm *.o
	

parser.o:moduletp4.h memory.h 
	gcc -c parser.c

moduletp4.o:
	gcc -c moduletp4.c

memory.o: memory.h
	gcc -c memory.c
main.o: main.h moduletp4.h parser.h memory.h
	gcc -c main.c
instructions.o: instructions.h memory.h
	gcc -c instructions.c
	
interpreteur.o: interpreteur.h memory.h parser.h instructions.h
	gcc -c interpreteur.c

clean:
	rm -rf *.o