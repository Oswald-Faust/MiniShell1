#include "my.h"

extern char **environ;

int is_directory(const char *filepath) {
    struct stat file_stat;
    if (stat(filepath, &file_stat) != 0) {
        return 0;
    }
    return S_ISDIR(file_stat.st_mode);
}

int my_execvp(char *file, char **args) {
    char *path = my_getenv("PATH");
    if (path == NULL) {
        perror("my_execvp: PATH variable not found");
        return -1;
    }
    
    if (strchr(file, '/')) {
         if (is_directory(file)) {
            errno = EACCES;
            perror(file);
            exit(EXIT_FAILURE);
        }
        if (execve(file, args, environ) == -1) {
            perror("my_execvp: Can not execute this file");
            return -1;
        }
    } else {
        char *path_copy = strdup(path);
        if (path_copy == NULL) {
            perror("my_execvp: Can not allocate memory");
            return -1;
        }
        char *token = strtok(path_copy, ":");
        while (token != NULL) {
            char *filepath = concat_filepath(token, file);
            if (filepath == NULL) {
                free(path_copy);
                perror("my_execvp: Can not allocate memory");
                return -1;
            }
            if (execve(filepath, args, environ) != -1) {
                free(filepath);
                break;
            } else if (errno != ENOENT) {
                perror("my_execvp: Can not execute this file");
                free(filepath);
                free(path_copy);
                return -1;
            }
            free(filepath);
            token = strtok(NULL, ":");
        }
        free(path_copy);
    }
    return 0;
}
