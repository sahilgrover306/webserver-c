#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.c"



void launch(struct Server *server){
    char buffer[30000];
    char *hello = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello world!";
    int address_length = sizeof(server->address);
    int new_socket;
    
    while (1)
    {
        printf("waiting for connn..........\n");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        recv(new_socket, buffer, 30000, 0);
        //read(new_socket, buffer, 30000);
        printf("%s\n\n", buffer);
        send(new_socket, hello, strlen(hello)+1, MSG_OOB);
    }
    closesocket(new_socket);
    WSACleanup();
    return;

}
int main(){
    printf("starting server\n");
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    printf("server started");
    server.launch(&server);
    
}
