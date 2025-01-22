#include "parser/command_parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_command(const char *input, Command *cmd) {
    if (!input || !cmd) {
        return -1;
    }

    memset(cmd, 0, sizeof(*cmd));

    char *buffer = strdup(input);
    char *rest = buffer;

    char *group = strtok_r(rest, ".", &rest);
    if (!group) {
        free(buffer);
        return -1;
    }
    strncpy(cmd->group, group, sizeof(cmd->group) - 1);

    char *token = strtok_r(rest, " ", &rest);
    if (!token) {
        free(buffer);
        return -1;
    }
    strncpy(cmd->name, token, sizeof(cmd->name) - 1);

    size_t arg_index = 0;
    while ((token = strtok_r(NULL, " ", &rest)) && arg_index < MAX_ARGS) {
        cmd->args[arg_index++] = strdup(token);
    }
    cmd->argc = arg_index;

    free(buffer);
    return 0;
}

