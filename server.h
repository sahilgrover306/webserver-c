#ifndef Server_h
#define Server_h

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

struct Server
{
    int domain; 
    int service;
    int protocol;
    u_long interfacee;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Server *server);

};

struct Server server_constructor(int domain, int service, int protocol, u_long interfacee, int port, int backlog, void (*launch)(struct Server *server));

#endif