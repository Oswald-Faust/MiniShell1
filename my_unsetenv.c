/*
** EPITECH PROJECT, 2023
** executing
** File description:
** executing
*/

#include "my.h"

extern char **environ;

void second_entity(char **p)
{
    char **q = p;
    while (*q != NULL) {
        *q = *(q + 1);
        q++;
    }
}

int my_unsetenv(const char *name)
{
    if (name == NULL || my_strlen(name) == 0 || my_strchr(name, '=') != NULL) {
        return -1;
    }
    for (char **p = environ; *p != NULL; p++) {
        if (my_strncmp(name, *p, my_strlen(name)) == 0 &&
        (*p)[my_strlen(name)] == '=') {
            second_entity(p);
            return 0;
        }
    }
    return -1;
}
