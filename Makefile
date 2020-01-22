CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = ./srcs/main.c ./srcs/stdin.c ./srcs/get_next_line.c ./srcs/get_next_line_utils.c ./srcs/fonction.c ./srcs/minishell_utils.c ./srcs/minishell_utils_2.c ./srcs/operation.c ./srcs/open_file.c ./srcs/cd.c ./srcs/quote.c ./srcs/fonction2.c
OBJS = ${SRCS:.c=.o}

NAME =	minishell

LIB =	minishell.a

LINK = ar rcs

${NAME}:	${OBJS}
			${LINK} ${LIB} ${OBJS}
			ranlib minishell.a
			${CC} ${CFLAGS} ${LIB} -o ${NAME}
			rm ${LIB}



all:		${NAME}

bonus:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f a.out

re: 		fclean all

.PHONY: all clean fclean re
