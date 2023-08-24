/*
** EPITECH PROJECT, 2023
** function_project.c
** File description:
** project.c
*/

#include "my.h"

char* search_absolute_path(char* command)
{
    if (command[0] == '/') {
        if (access(command, X_OK) == 0) {
            return my_strdup(command);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

char* get_next_dir(char* current_dir, char* end_path)
{
    char* next_dir = my_strchr(current_dir, ':');
    if (next_dir == NULL) {
        return end_path;
    } else {
        return next_dir + 1;
    }
}

char* search_relative_path(char* command, char* path)
{
    char buffer[MAX_BUFFER_SIZE];
    char* path_env = my_getenv(path);
    if (path_env == NULL || my_strchr(command, '/') != NULL) {
        return NULL;
    }
    char* end_path = path_env + my_strlen(path_env);
    for (char* dir = path_env; dir != end_path;
    dir == get_next_dir(dir, end_path)) {
        int dir_len = my_strcspn(dir, ":");
        if (dir_len >= MAX_BUFFER_SIZE) {
            continue;
        }
        my_strncpy(buffer, dir, dir_len);
        buffer[dir_len] = '/';
        my_strncpy(buffer + dir_len + 1, command,
        MAX_BUFFER_SIZE - dir_len - 1);
        if (access(buffer, X_OK) == 0) {
            return my_strdup(buffer);
        }
    }
}

char* search_path(char* command, char* path)
{
    char* result = search_absolute_path(command);
    if (result != NULL) {
        return result;
    }
    result = search_relative_path(command, path);
    return result;
}
