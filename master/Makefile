all: main
	./main
	
main: main.o 
	gcc -Wall -o main main.c data.c calculator.c -lpthread -lm

clean:
	rm -f main *.o
