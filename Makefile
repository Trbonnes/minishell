CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = 
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
