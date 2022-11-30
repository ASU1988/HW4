# Makefile for World project

Weather: main.o libjson.a
	gcc -o Weather main.o -lcurl -L. -ljson -lm

main.o: main.c
	gcc main.c -c    

libjson.a: json.o
	ar cr libjson.a json.o

json.o: json.c
	gcc -c json.c

clean:
	rm -f *.o *.a binary