all: main
	./main
	
main: main.o 
	gcc -Wall -o main main.c -lpthread
	
mainCliente.o: mainCliente.c 
	gcc -c mainCliente.c 

clean:
	rm -f main *.o
