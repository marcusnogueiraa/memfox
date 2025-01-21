#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

// Configuração do servidor
#define SERVER_PORT 8080
#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024

// Estrutura para encapsular o estado do servidor
typedef struct {
    int server_fd;               // File descriptor do socket do servidor
    struct sockaddr_in address;  // Endereço do servidor
    int addrlen;                 // Tamanho do endereço
} Server;

// Funções públicas
int socket_init(Server *server);
int socket_accept(Server *server);
int socket_read(int client_fd, char *buffer, size_t size);
int socket_send(int client_fd, const char *message, size_t size);
void socket_close(int fd);

#endif // SERVER_H
