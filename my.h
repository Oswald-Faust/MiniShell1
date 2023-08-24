/*
** EPITECH PROJECT, 2023
** my_file
** File description:
** file_of_my
*/

#ifndef _my_h_
    #define _my_h_
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/wait.h>
    #include <errno.h>
    #include <sys/stat.h>
    #include <limits.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <ctype.h>
    #define MAX_BUFFER_SIZE 1024
    #define MAX_ARGS 64
    #define MAX_INPUT_LENGTH 1024

typedef struct {
    char* input;
    int i;
    int loop;
} ReadInputContext;

char* search_path(char* command, char* path);
char* search_absolute_path(char* command);
void execute_setenv(char** arguments);
void execute_unsetenv(char** arguments);
void execute_env(void);
char** parse_input(char* input);
void execute_exit(char** arguments);
char* search_relative_path(char* command, char* path);
char* get_next_dir(char* current_dir, char* end_path);
char* search_path(char* command, char* path);
void execute_command(char** arguments);
int is_valid_argument(const char* arg);
int parse_argument(const char* arg);
void execute_cd(char** arguments);
void my_putchar(char c);
int my_putstr(char *str);
void execute_exit(char** arguments);
void my_putchar(char c);
char** parse_input(char* input);
int is_builtin(char* command);
void execute_builtin(char** arguments);
void handle_parent_process(void);
int main(void);
void process_input(char* input);
void handle_child_process(char** arguments);
char* get_executable_path(char* file);
void print_prompt(void);
int is_builtin(char* command);
char* get_input(void);
void handle_parent_process(void);
void execute_commando(char** arguments);
char *my_strcpy(char *dest, const char *src);
char* my_strncpy(char* dest, const char* src, size_t n);
int my_strcmp(const char *str, const char *str0);
int my_strncmp(const char *str1, const char *str2, int nbr);
int my_strlen(const char *str);
char *my_strdup(char *str);
void inutile(char **arguments);
size_t my_strcspn(const char* str, const char* reject);
static char **get_existing_env_var(const char *name);
static void add_or_modify_env_var(const char *name,
const char *value, int overwrite);
char* my_strchr(const char* str, int c);
char* my_getenv(const char* name);
char* my_strcat(char *dest, const char *src);
static void add_or_modify_env_var(const char *name,
const char *value, int overwrite);
int my_execvp(char* file, char** args);
int my_unsetenv(const char *name);
int my_setenv(const char *name, const char *value, int overwrite);
void second_entity(char **p);
int my_execv(const char *path, char *const argv[]);
char* concat_filepath(char* token, char* file);
char* search_pathy(char* path, char* file);
void process_char(char c, ReadInputContext* context);
void process_read_result(ssize_t read_result, char c,
ReadInputContext* context);

#endif
