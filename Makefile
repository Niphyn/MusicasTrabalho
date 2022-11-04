libtads.a: tads/Musica.c tads/Vector.c tads/Musica.h tads/Vector.h
	gcc -c tads/Musica.c -o tads/Musica.o
	gcc -c tads/Vector.c -o tads/Vector.o
	ar -crs libtads.a tads/Musica.o tads/Vector.o
all: libtads.a main.c
	gcc -o main main.c -I tads -L . -ltads
run:
	./main
val:
	valgrind ./main
clean:
	rm -f *.a *.o tads/*.o main