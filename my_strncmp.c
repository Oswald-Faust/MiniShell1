/*
** EPITECH PROJECT, 2023
** strncmp.c
** File description:
** strncmp
*/

#include "my.h"

int my_strncmp(const char *str1, const char *str2, int nbr)
{
    int a;
    if (str1 == NULL || str2 == NULL)
        return (-1);
    a = 0;
    while (str1[a] && str2[a] && a < nbr) {
        if (str1[a] != str2[a])
            return (str1[a] - str2[a]);
        a += 1;
    }
    if (a < nbr)
        return (-1);
    return (0);
}
