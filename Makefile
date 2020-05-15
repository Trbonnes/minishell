CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS = ./srcs/main.c ./srcs/stdin.c ./srcs/get_next_line.c ./srcs/get_next_line_utils.c ./srcs/fonction.c ./srcs/minishell_utils.c ./srcs/minishell_utils_2.c ./srcs/operation.c ./srcs/open_file.c ./srcs/cd.c ./srcs/quote.c ./srcs/fonction2.c ./srcs/minishell_utils_3.c ./srcs/env_parsing.c ./srcs/builtin_incrementers.c ./srcs/parser_str.c ./srcs/redirection.c ./srcs/redirection_quote.c ./srcs/ft_split.c ./srcs/ft_split_2.c ./srcs/ft_execute_cmd.c ./srcs/pipe.c ./srcs/lst.c ./srcs/stdin2.c ./srcs/dollar_env.c ./srcs/minishell_utils_4.c ./srcs/ft_itoa.c ./srcs/unquote.c ./srcs/minishell_utils_5.c ./srcs/unquote_utils.c ./srcs/ft_atoi.c ./srcs/error_env_builtin.c ./srcs/ft_split_libft.c ./srcs/quote_executable.c ./srcs/minishell_utils_6.c ./srcs/lst2.c ./srcs/ft_split_export.c ./srcs/fonction3.c ./srcs/minishell_utils_7.c ./srcs/escape_character.c ./srcs/escape_character_2.c ./srcs/pipe_prompt.c
OBJS = ${SRCS:.c=.o}

NAME =	minishell

LIB =	minishell.a

LINK = ar rcs

all:
	$(MAKE) ${NAME} -j

${NAME}:	${OBJS}
			${LINK} ${LIB} ${OBJS}
			ranlib minishell.a
			${CC} ${CFLAGS} ${LIB} -o ${NAME}
			rm ${LIB}




bonus:		${NAME}

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f a.out

re: 		fclean all

.PHONY: all clean fclean re
