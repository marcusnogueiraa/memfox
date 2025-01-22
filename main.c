#include "network/server.h"
#include "parser/command_parser.h"
#include <stdio.h>
#include <string.h>

int main() {
    Server server;
    char buffer[BUFFER_SIZE];

    if (socket_init(&server) != 0) {
        return -1;
    }

    while (1) {
        int client_fd = socket_accept(&server);
        if (client_fd < 0) {
            continue;
        }

        int bytes_read = socket_read(client_fd, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            printf("[info] Received: %s\n", buffer);

            Command command;
            if (parse_command(buffer, &command) == 0){
                
            } else {
                perror("[error] parsing error\n");
            }
        }

        socket_close(client_fd);
    }

    socket_close(server.server_fd);
    return 0;
}
