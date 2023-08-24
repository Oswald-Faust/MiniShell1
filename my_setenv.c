/*
** EPITECH PROJECT, 2023
** first_projct.c
** File description:
** beginning.c
*/

#include "my.h"

extern char **environ;
char **my_environ = NULL;

int my_isalpha(int c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int is_alphanumeric(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

int is_alphanumeric_string(const char *str) {
    if (str == NULL || !my_isalpha(str[0])) {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_alphanumeric(str[i])) {
            return 0;
        }
    }

    return 1;
}

static char **get_existing_env_var(const char *name)
{
    if (my_environ == NULL)
        return NULL;

    for (char **p = my_environ; *p != NULL; p++) {
        if (my_strncmp(name, *p, my_strlen(name)) == 0 &&
        (*p)[my_strlen(name)] == '=') {
            return p;
        }
    }
    return NULL;
}

static void add_or_modify_env_var(const char *name, const char *value, int overwrite)
{
    char **existing_var = get_existing_env_var(name);
    if (existing_var) {
        if (!overwrite) {
            return;
        }
        char *new_var = (char *) malloc(my_strlen(name) + my_strlen(value) + 2);
        my_strcpy(new_var, name);
        my_strcat(new_var, "=");
        my_strcat(new_var, value);
        *existing_var = new_var;
    } else {
        size_t env_len = 0;
        while (environ[env_len] != NULL) env_len++;

        if (my_environ == NULL) {
            my_environ = malloc((env_len + 2) * sizeof(char *));
            for (size_t i = 0; i < env_len; i++) {
                my_environ[i] = environ[i];
            }
            my_environ[env_len] = NULL;
        } else {
            my_environ = realloc(my_environ, (env_len + 2) * sizeof(char *));
            if (!my_environ) {
                perror("realloc");
                return;
            }
        }

        char *new_var = (char *) malloc(my_strlen(name) + my_strlen(value) + 2);
        my_strcpy(new_var, name);
        my_strcat(new_var, "=");
        my_strcat(new_var, value);
        my_environ[env_len] = new_var;
        my_environ[env_len + 1] = NULL;

        environ = my_environ;
    }
}

int my_setenv(const char *name, const char *value, int overwrite) {
    if (name == NULL || my_strlen(name) == 0 || !is_alphanumeric_string(name) || value == NULL) {
        return -1;
    }
    add_or_modify_env_var(name, value, overwrite);
    return 0;
}

