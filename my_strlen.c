/*
** EPITECH PROJECT, 2023
** my_strlenc
** File description:
** strlen
*/

#include "my.h"

int my_strlen(const char *str)
{
    int a = 0;
    while (str != NULL && str[a])
        a += 1;
    return (a);
}
