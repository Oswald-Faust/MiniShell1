#include "my.h"
#include <fcntl.h>

void handle_parent_process(void)
{
    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        my_putstr("");
    } else if (WIFSIGNALED(status)) {
        my_putstr("");
    }
}

char* trim_whitespace(char* str) {
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == 0) {
        return str;
    }

    char* end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    end[1] = '\0';

    return str;
}

int redirect_output(char* filename) {
    int out = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0600); 
    if (-1 == out) { 
        fprintf(stderr, "Erreur lors de l'ouverture du fichier '%s' pour la redirection de sortie: %s\n", filename, strerror(errno));
        return -1; 
    }

    int save_out = dup(fileno(stdout));

    if (-1 == save_out) {
        fprintf(stderr, "Erreur lors de la sauvegarde de stdout: %s\n", strerror(errno));
        close(out);
        return -1;
    }

    if (-1 == dup2(out, fileno(stdout))) { 
        fprintf(stderr, "Impossible de rediriger stdout: %s\n", strerror(errno));
        close(save_out);
        close(out);
        return -1;
    }

    if (-1 == close(out)) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier '%s' après redirection: %s\n", filename, strerror(errno));
    }

    return save_out;
}

int redirect_input(char* filename) {
    int in = open(filename, O_RDONLY); 
    if (-1 == in) { 
        fprintf(stderr, "Erreur lors de l'ouverture du fichier '%s' pour la redirection d'entrée: %s\n", filename, strerror(errno));
        return -1; 
    }

    int save_in = dup(fileno(stdin));

    if (-1 == save_in) {
        fprintf(stderr, "Erreur lors de la sauvegarde de stdin: %s\n", strerror(errno));
        close(in);
        return -1;
    }

    if (-1 == dup2(in, fileno(stdin))) { 
        fprintf(stderr, "Impossible de rediriger stdin: %s\n", strerror(errno));
        close(save_in);
        close(in);
        return -1;
    }

    if (-1 == close(in)) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier '%s' après redirection: %s\n", filename, strerror(errno));
    }

    return save_in;
}

void reset_output(int saved_stdout) {
    if (-1 == fflush(stdout)) {
        fprintf(stderr, "Erreur lors de l'évacuation de stdout: %s\n", strerror(errno));
    }

    if (-1 == close(fileno(stdout))) {
        fprintf(stderr, "Erreur lors de la fermeture de stdout: %s\n", strerror(errno));
    }

    if (-1 == dup2(saved_stdout, fileno(stdout))) {
        fprintf(stderr, "Impossible de restaurer stdout: %s\n", strerror(errno));
    }

    if (-1 == close(saved_stdout)) {
        fprintf(stderr, "Erreur lors de la fermeture de la sauvegarde de stdout: %s\n", strerror(errno));
    }
}

void reset_input(int saved_stdin) {
    if (-1 == fflush(stdin)) {
        fprintf(stderr, "Erreur lors de l'évacuation de stdin: %s\n", strerror(errno));
    }

    if (-1 == close(fileno(stdin))) {
               fprintf(stderr, "Impossible de restaurer stdin: %s\n", strerror(errno));
    }

    if (-1 == close(saved_stdin)) {
        fprintf(stderr, "Erreur lors de la fermeture de la sauvegarde de stdin: %s\n", strerror(errno));
    }
}

char* next_command(char* input, char delimiter) {
    static char* current_position;
    if (input != NULL) {
        current_position = input;
    }
    if (current_position == NULL || *current_position == '\0') {
        return NULL;
    }

    char* start = current_position;
    char* end = strchr(start, delimiter);

    if (end != NULL) {
        *end = '\0';
        current_position = end + 1;
    } else {
        current_position = NULL;
    }

    return start;
}

int redirect_output_append(char* filename) {
    int out = open(filename, O_RDWR | O_CREAT | O_APPEND, 0600); 
    if (-1 == out) { 
        perror("opening file"); 
        return -1; 
    }

    int save_out = dup(fileno(stdout));

    if (-1 == dup2(out, fileno(stdout))) { 
        perror("cannot redirect stdout"); 
        return -1;
    }
    return save_out;
}

char* read_heredoc(char* delimiter) {
    char* input = NULL;
    size_t len = 0;
    ssize_t read;
    char* heredoc = NULL;

    while ((read = getline(&input, &len, stdin)) != -1) {
        if (strncmp(input, delimiter, strlen(delimiter)) == 0) {
            break;
        }
        char* old_heredoc = heredoc;
        if (heredoc == NULL) {
            heredoc = strdup(input);
        } else {
            asprintf(&heredoc, "%s%s", heredoc, input);
        }
        free(old_heredoc);
    }

    free(input);

    return heredoc;
}

int last_command_status = 0;

char* get_logic_operator(char* command) {
    if (strstr(command, "&&") != NULL) {
        return "&&";
    } else if (strstr(command, "||") != NULL) {
        return "||";
    } else {
        return NULL;
    }
}

void process_input(char* input) {
    char* command = next_command(input, ';');
    while (command != NULL) {
        char* output_redirect = strchr(command, '>');
        char* input_redirect = strchr(command, '<');
        char* filename = NULL;
        int saved_stdout = -1;
        int saved_stdin = -1;

        if (output_redirect != NULL) {
            *output_redirect = '\0';
            filename = output_redirect + 1;
            filename = trim_whitespace(filename);
            if (*(output_redirect + 1) == '>') { // Si le caractère après '>' est aussi '>', alors c'est une redirection en mode "append"
                filename++; // On décale le pointeur de fichier pour ne pas inclure le deuxième '>'
                saved_stdout = redirect_output_append(filename);
            } else {
                saved_stdout = redirect_output(filename);
            }
            if (saved_stdout == -1) {
                fprintf(stderr, "Erreur de redirection de sortie.\n");
                command = next_command(NULL, ';');
                continue;
            }
        }

        char* heredoc_start = strstr(command, "<<");
        char* heredoc_input = NULL;

        if (heredoc_start != NULL) {
            *heredoc_start = '\0';
            char* heredoc_delimiter = heredoc_start + 2;
            heredoc_delimiter = trim_whitespace(heredoc_delimiter);
            heredoc_input = read_heredoc(heredoc_delimiter);
        }


        if (input_redirect != NULL) {
            *input_redirect = '\0';
            filename = input_redirect + 1;
            filename = trim_whitespace(filename);
            saved_stdin = redirect_input(filename);
            if (saved_stdin == -1) {
                fprintf(stderr, "Erreur de redirection d'entrée.\n");
                command = next_command(NULL, ';');
                continue;
            }
        }

        char** arguments = parse_input(command);
        if (arguments[0] == NULL) {
            free(arguments);
        } else {
            if (is_builtin(arguments[0])) {
                execute_builtin(arguments);
            } else {
                execute_commando(arguments);
            }
            free(arguments);
        }

        if (output_redirect != NULL) {
            reset_output(saved_stdout);
        }

        if (input_redirect != NULL) {
            reset_input(saved_stdin);
        }

        if (heredoc_start != NULL) {
            free(heredoc_input);
        }

        char* logic_operator = get_logic_operator(command);
        if (logic_operator != NULL) {
            // Récupérer la prochaine commande
            char* next_commandi = next_command(NULL, ';');
            if (next_commandi != NULL) {
                // Exécuter la prochaine commande si les conditions sont respectées
                if ((strcmp(logic_operator, "&&") == 0 && last_command_status == 0) ||
                    (strcmp(logic_operator, "||") == 0 && last_command_status != 0)) {
                    command = next_commandi;
                    continue;
                }
            }
        }
        command = next_command(NULL, ';');
    }
}

int main(void)
{
    while (1) {
        print_prompt();
        char* input = get_input();
        process_input(input);
        free(input);
    }
    return 0;
}


