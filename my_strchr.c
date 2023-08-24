/*
** EPITECH PROJECT, 2023
** strdup_function.c
** File description:
** function
*/

#include "my.h"

char* my_strchr(const char* str, int c)
{
    while (*str != '\0') {
        if (*str == c) {
            return (char*) str;
        }
        str++;
    }
    return NULL;
}
