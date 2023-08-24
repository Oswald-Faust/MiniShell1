/*
** EPITECH PROJECT, 2023
** function_project.c
** File description:
** project.c
*/

#include "my.h"

extern char **environ;

char* my_getenv(const char* name)
{
    char** p = environ;
    size_t namelen = my_strlen(name);
    while (*p) {
        if (my_strncmp(*p, name, namelen) == 0
        && (*p)[namelen] == '=') {
            return *p + namelen + 1;
        }
        p++;
    }
    return NULL;
}
