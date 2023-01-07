all: main
	./main
	
main: main.o 
	gcc -Wall -o main main.c data.c calculator.c utility/node.c utility/list.c domain/slave.c socket.c -lpthread -lm

clean:
	rm -f main *.o
