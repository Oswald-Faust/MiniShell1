/*
** EPITECH PROJECT, 2023
** final.c
** File description:
** builtin.c
*/
#include "my.h"


int is_builtin(char* command)
{
    return (my_strcmp(command, "cd") == 0 || my_strcmp(command, "exit") == 0 ||
    my_strcmp(command, "setenv") == 0 || my_strcmp(command, "unsetenv") == 0 ||
    my_strcmp(command, "env") == 0);
}

void execute_builtin(char** arguments)
{
    if (my_strcmp(arguments[0], "cd") == 0) {
        execute_cd(arguments);
        return;
    }
    if (my_strcmp(arguments[0], "exit") == 0) {
        execute_exit(arguments);
        return;
    }
    if (my_strcmp(arguments[0], "setenv") == 0) {
        execute_setenv(arguments);
        return;
    }
    if (my_strcmp(arguments[0], "unsetenv") == 0) {
        execute_unsetenv(arguments);
        return;
    }
    inutile(arguments);
}

void inutile(char **arguments)
{
    if (my_strcmp(arguments[0], "env") == 0) {
        execute_env();
        return;
    }
    my_putstr(arguments[0]);
    my_putstr(": command not found\n");
}
