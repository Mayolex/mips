all: memory.o main.o parser.o moduletp4.o  instructions.o 
	gcc -o exe moduletp4.o parser.o main.o memory.o instructions.o -lm
	rm *.o
	./exe tests/in3.txt out_hex.txt
	

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
	

clean:
	rm -rf *.o