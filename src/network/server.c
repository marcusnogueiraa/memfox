#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
	Author: Marcus Nogueira
	Description: Initialize the server socket
*/
int socket_init(Server *server) {
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server->server_fd == 0) {
        perror("[error] socket failed");
        return -1;
    }

    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(SERVER_PORT);
    server->addrlen = sizeof(server->address);

    if (bind(server->server_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0) {
        perror("[error] bind failed");
        close(server->server_fd);
        return -1;
    }

    if (listen(server->server_fd, MAX_CONNECTIONS) < 0) {
        perror("[error] listen failed");
        close(server->server_fd);
        return -1;
    }

    printf("[info] server listening on port %d...\n", SERVER_PORT);
    return 0;
}

/*
	Author: Marcus Nogueira
	Description: Accepts socket connection
*/
int socket_accept(Server *server) {
    int client_fd = accept(server->server_fd, (struct sockaddr *)&server->address, (socklen_t *)&server->addrlen);
    if (client_fd < 0) {
        perror("[error] accept failed");
        return -1;
    }

    printf("[info] client connected!\n");
    return client_fd;
}

/*
	Author: Marcus Nogueira
	Description: Read client data
*/
int socket_read(int client_fd, char *buffer, size_t size) {
    memset(buffer, 0, size);
    int bytes_read = read(client_fd, buffer, size - 1);
    if (bytes_read < 0) {
        perror("[error] read failed");
    }
    return bytes_read;
}

/*
	Author: Marcus Nogueira
	Description: Send data to client
*/
int socket_send(int client_fd, const char *message, size_t size) {
    int bytes_sent = send(client_fd, message, size, 0);
    if (bytes_sent < 0) {
        perror("[error] send failed");
    }
    return bytes_sent;
}

/*
	Author: Marcus Nogueira
	Description: Close server socket
*/
void socket_close(int fd) {
    close(fd);
    printf("Socket closed\n");
}
