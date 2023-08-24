/*
** EPITECH PROJECT, 2023
** function_project.c
** File description:
** project_again.c
*/

#include "my.h"

char* get_executable_path(char* file)
{
    char* path = my_getenv("PATH");
    if (path == NULL) {
        return NULL;
    }
    return search_pathy(path, file);
}

char* search_pathy(char* path, char* file)
{
    char* path_copy = my_strdup(path);
    if (path_copy == NULL) {
        return NULL;
    }
    char* token = strtok(path_copy, ":");
    while (token != NULL) {
        char* filepath = concat_filepath(token, file);
        if (filepath == NULL) {
            free(path_copy);
            return NULL;
        }
        if (access(filepath, X_OK) == 0) {
            free(path_copy);
            return filepath;
        }
        free(filepath);
        token = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

char* concat_filepath(char* token, char* file)
{
    char* filepath = malloc(my_strlen(token) +
    my_strlen(file) + 2);
    if (filepath == NULL) {
        return NULL;
    }
    my_strcpy(filepath, token);
    my_strcat(filepath, "/");
    my_strcat(filepath, file);
    return filepath;
}
