/*
** EPITECH PROJECT, 2023
** inputing
** File description:
** input
*/

#include "my.h"

void process_read_result(ssize_t read_result, char c, ReadInputContext* context)
{
    if (read_result == 0) {
        handle_sort(context->input, context->i);
        context->loop = 0;
    } else if (read_result == -1) {
        handle_read_error(context->input);
    } else {
        process_char(c, context);
    }
}

void process_char(char c, ReadInputContext* context)
{
    if (c == '\n') {
        context->loop = 0;
    } else {
        context->input[(context->i)++] = c;
    }
}

void execute_commando(char** arguments) {
    pid_t pid = fork();

    if (pid == 0) {
        // Nous sommes dans le processus enfant
        handle_child_process(arguments);
    } else if (pid < 0) {
        // Erreur lors du fork
        perror("fork");
    } else {
        // Nous sommes dans le processus parent
        handle_parent_process();
    }
}

void handle_child_process(char** arguments)
{
    if (my_execvp(arguments[0], arguments) == -1) {
        switch (errno) {
            case ENOENT:
                perror("Command not found");
                break;
            case EACCES:
                perror("Permission denied");
                break;
            case ENOEXEC:
                perror("Exec format error. Wrong Architecture");
                break;
            default:
                perror("exec");
        }
        exit(EXIT_FAILURE);
    }
}
