#include "server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_constructor(int domain, int service, int protocol, u_long interfacee, int port, int backlog, void (*launch)(struct Server *server)){
	
    struct Server server;

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interfacee = interfacee;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interfacee);

    WSADATA wsa;
	SOCKET s;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(1);
	}
    server.socket = socket(domain, service, protocol);

    if(server.socket == INVALID_SOCKET ){
        perror("Failed to connect socket...\n");
        exit(1);
    }

    printf("Socket created...\n");
    if(bind(server.socket, (struct sockaddr *)&server.address, sizeof(server)) < 0){
        perror("Failed to bind socket...\n");
        exit(1);
    }

    if(listen(server.socket, backlog) < 0){
        perror("Failed to start listening...\n");
        exit(1);
    }

    server.launch = launch;
    
    return server;
}