/*
** EPITECH PROJECT, 2023
** strdup_function.c
** File description:
** function
*/

#include "my.h"

char* my_strcat(char *dest, const char *src)
{
    size_t dest_len = my_strlen(dest);
    size_t i;

    for (i = 0; src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}
