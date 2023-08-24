##
## EPITECH PROJECT, 2023
## solvefile
## File description:
## solvef
##

SRC     =    	builtin_exercice.c		\
				executing.c		\
				function.c 		\
				input.c 		\
				input1.c 		\
				my_getenv.c 	\
				my_putchar.c 	\
				my_putstr.c 	\
				my_setenv.c 	\
				my_strcat.c 	\
				my_strchr.c 	\
				my_strcmp.c 	\
				my_strncmp.c 	\
				my_strlen.c 	\
				my_strncpy.c 	\
				my_strdup.c 	\
				my_strcspn.c 	\
				my_execvp.c 	\
				my_execvp1.c	\
				my_strcpy.c		\
				my_unsetenv.c	\
				builtin_final.c	\
				input_second.c

OBJ     =       $(SRC:.c=.o)

NAME    =       mysh

all:    $(NAME)

$(NAME):        $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:  fclean all
