/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:31:36 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/27 15:23:25 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdio.h> // a enlever

typedef struct		s_env
{
	char			*key;
	char			*ref;
	struct s_env	*next;
}					t_env;
typedef struct		s_parsing
{
	int					builtin_detected;
	char				*executable;
	int					echo_option;
	char				*param;
	char				*redirection;
	int					index;
	struct s_parsing	*next;
}					t_parsing;

int					ft_detect_builtin(char **env);
int					ft_tolower(int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin(const char *s1, char *s2);
char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *str);
void				ft_bzero(void *s, size_t n);
void				ft_envdelone(t_env *lst);
void				ft_envclear(t_env **lst);
char				*ft_strdup_chr(const char *str, char c);
size_t				ft_strlen_chr(const char *str, char c);
int					ft_wait_quote(char c, char **quote_str);
int					ft_redirection_calculate(int i, char **str, char **q);
void				ft_unquote(char **str);
void				ft_environment_parsing(char **env);
int					ft_redirection_quote(int i, char **str,
char **quote_str, char c);
int					ft_increment_begin(char *str, int i);
int					ft_increment_end(char *str, int i);
int					ft_increment_option(char *str, int i, t_parsing *parser);
int					ft_parser_get(t_parsing *parser, char *str, int i);
char				*ft_parser_param(char *str);
char				*ft_parser_redirection(char **builtin_str);
int					ft_option(char *str, t_parsing *parser, int i);
void				ft_quote_cpy(int i, int j, char **redirection, char **q);
int					ft_quote_check(char c, int quote);
char				*ft_realloc_param_str(int i, int j, char *param_str);
void				ft_parserclear(t_parsing **lst);
char				**ft_split(char const *str, char c);
char				**ft_no_args(void);
int					ft_execute_builtin(t_parsing *parser, char **env);

#endif
