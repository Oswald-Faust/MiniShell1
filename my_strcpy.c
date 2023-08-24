/*
** EPITECH PROJECT, 2023
** strdup_function.c
** File description:
** function
*/

#include "my.h"

char *my_strcpy(char *dest, const char *src)
{
    char *result = dest;
    while ((*dest++ = *src++) != '\0');
    return result;
}
