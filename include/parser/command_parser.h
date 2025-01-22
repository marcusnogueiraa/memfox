#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stddef.h>

#define MAX_ARGS 10

typedef struct {
    char group[32];
    char name[32];
    char *args[MAX_ARGS]; 
    size_t argc;          
} Command;

int parse_command(const char *input, Command *cmd);

#endif
