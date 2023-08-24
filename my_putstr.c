/*
** EPITECH PROJECT, 2023
** puts_implementation.c
** File description:
** implementation
*/

#include "my.h"

int my_putstr(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i +1;
    }
}
