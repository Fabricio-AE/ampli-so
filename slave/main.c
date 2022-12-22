#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

void initSocket();

int main(int argc, char** argv){
    printf("Hola estoy aquí\n");
    initSocket();
    return 0;
}

void initSocket(){
    while(1){
        struct sockaddr_in addr;
        
    }
}