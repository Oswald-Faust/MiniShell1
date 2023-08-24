/*
** EPITECH PROJECT, 2023
** builtin_exercice.c
** File description:
** builtin.c
*/

#include "my.h"

void execute_exit(char** arguments)
{
    int exit_code = EXIT_SUCCESS;
    if (arguments[1] != NULL) {
        const char* arg = arguments[1];
        int sign = 1;
        if (*arg == '-') {
            sign = -1;
            arg++;
        }
        if (!is_valid_argument(arg)) {
            my_putstr("Invalid argument");
            return;
        }
        exit_code = parse_argument(arg) * sign;
    }
    exit(exit_code);
}

int is_valid_argument(const char* arg)
{
    while (*arg != '\0') {
        if (*arg < '0' || *arg > '9') {
            return 0;
        }
        arg++;
    }
    return 1;
}

int parse_argument(const char* arg)
{
    int exit_code = 0;
    while (*arg != '\0') {
        exit_code = exit_code * 10 + (*arg - '0');
        arg++;
    }
    return exit_code;
}

char** parse_input(char* input)
{
    char** arguments = malloc(MAX_ARGS * sizeof(char*));
    char* argument = strtok(input, " \t\n");
    int i = 0;
    while (argument != NULL) {
        arguments[i] = argument;
        i++;
        argument = strtok(NULL, " \t\n");
    }
    arguments[i] = NULL;
    return arguments;
}
