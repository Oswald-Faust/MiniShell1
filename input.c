/*
** EPITECH PROJECT, 2023
** inputing
** File description:
** input
*/

#include "my.h"

void print_prompt(void)
{
    my_putstr(">$ ");
}

void handle_read_error(char* input)
{
    perror("get_input: read error");
    free(input);
    exit(EXIT_FAILURE);
}

void handle_sort(char* input, int i)
{
    if (i == 0) {
        free(input);
        exit(EXIT_SUCCESS);
    }
}

char* get_input(void)
{
    char* input = malloc(MAX_INPUT_LENGTH);
    if (input == NULL) {
        return NULL;
    }
    int i = 0;
    char c;
    int loop = 1;
    ReadInputContext context = {input, i, loop};
    while (context.loop && context.i < MAX_INPUT_LENGTH - 1) {
        ssize_t read_result = read(STDIN_FILENO, &c, 1);
        process_read_result(read_result, c, &context);
    }
    input[context.i] = '\0';
    return input;
}
