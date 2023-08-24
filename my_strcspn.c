/*
** EPITECH PROJECT, 2023
** first_project.c
** File description:
** beginning.c
*/

#include "my.h"

size_t my_strcspn(const char* str, const char* reject)
{
    size_t count = 0;
    while (*str != '\0') {
        if (my_strchr(reject, *str) != NULL) {
            return count;
        }
        str++;
        count++;
    }
    return count;
}
