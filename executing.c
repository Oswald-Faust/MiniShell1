/*
** EPITECH PROJECT, 2023
** executing
** File description:
** executing
*/

#include "my.h"

void execute_cd(char** arguments)
{
    if (arguments[1] == NULL) {
        chdir(my_getenv("HOME"));
    } else {
        if (chdir(arguments[1]) == -1) {
            char* error_message = strerror(errno);
            char* message = "";
            my_putstr(message);
            my_putstr(arguments[1]);
            my_putstr(": ");
            my_putstr(error_message);
            my_putstr("\n");
        }
    }
}

void execute_setenv(char** arguments)
{
    if (arguments[1] == NULL) {
        my_putstr("Too few arguments.\n");
        return;
    }
    if (arguments[3] != NULL) {
        my_putstr("setenv: Too many arguments.\n");
        return;
    }
    char* name = arguments[1];
    char* value = arguments[2];
    if (my_setenv(name, value != NULL ? value : "", 1) == -1) {
        my_putstr("Command not found");
    }
}

void execute_unsetenv(char** arguments)
{
    if (arguments[1] == NULL) {
        my_putstr("Unsetenv: Too few arguments.\n");
        return;
    }
    if (arguments[2] != NULL) {
    my_putstr("unsetenv: Too many arguments.\n");
    return;
    }
    if (my_unsetenv(arguments[1]) == -1) {
    perror("unsetenv");
    }
}

void execute_env(void)
{
    extern char** environ;
    for (char** env = environ; *env != NULL; env++) {
        char* env_variable = *env;
        my_putstr(env_variable);
        my_putstr("\n");
    }
}
