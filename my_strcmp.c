/*
** EPITECH PROJECT, 2023
** str_compare
** File description:
** comparaison
*/

#include "my.h"

int my_strcmp(const char *str, const char *str0)
{
    int i;
    if (str == NULL || str0 == NULL)
        return (0);
    i = 0;
    while (str[i] != '\0' && str0[i] != '\0') {
        if (str[i] != str0[i])
            return (str[i] - str0[i]);
        i += 1;
    }
}
