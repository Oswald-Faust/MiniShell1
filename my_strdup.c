/*
** EPITECH PROJECT, 2023
** strdup_function.c
** File description:
** function
*/

#include "my.h"

char *my_strdup(char *str)
{
    char *dup = malloc(my_strlen(str) + 1);
    if (dup == NULL) {
        return NULL;
    }
    my_strcpy(dup, str);
    return dup;
}
