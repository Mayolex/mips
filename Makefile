all:parser.o moduletp4.o main.o
	gcc -o exe moduletp4.o parser.o main.o -lm
	rm *.o
	./exe tests/in2.txt out_hex.txt
	

parser.o:moduletp4.h parser.h
	gcc -c parser.c

moduletp4.o:
	gcc -c moduletp4.c

main.o: moduletp4.h parser.h
	gcc -c main.c

clean:
	rm -rf *.o