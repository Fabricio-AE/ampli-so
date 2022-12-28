all: main
	./main
	
main: main.o 
	gcc -Wall -o main main.c data.c -lpthread

clean:
	rm -f main *.o
