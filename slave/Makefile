all: main
	./main
	
main: main.o 
	gcc -Wall -o main main.c socket.c slave.c utility/node.c utility/list.c -lpthread

clean:
	rm -f main *.o
