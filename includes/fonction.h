/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:19 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/10 08:12:58 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONCTION_H
# define FONCTION_H
# include <string.h>
# include <errno.h>
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# define TRUE 1
# define FALSE 0

typedef	struct	s_fd
{
	int			in;
	int			out;
	int			pipe[2];
}				t_fd;

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
int					ft_executable(t_parsing *parser, char **env, t_fd *fd);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *str);
char				*ft_whitespace(char *str);
char				*ft_strjoin(const char *s1, char *s2);
void				ft_home(t_parsing *alk);
int					ft_up_directory(t_parsing *alk);
int					ft_cd(t_parsing *alk);
int					ft_echo(t_parsing *alk, t_fd *fd);
int					ft_pwd(t_fd *fd);
void				ft_exit(void);
int					ft_env_display(t_fd *fd);
int					ft_export(t_fd *fd, t_parsing *alk);
int					ft_unset(t_parsing *alk);
int					find_fd(t_parsing *alk, char **env);
int					superior(t_parsing *alk, int dbchevron, t_fd *fd);
int					inferior(t_parsing *alk, int dbchevron, t_fd *fd);
int					open_file(t_parsing *alk, t_fd *fd);
char				*skip_file(char *str);
char				*file_name(char *str);
char				*skip_operation(char *str);
int					strlen_word_file(char *str);
t_env				*ft_new_env(char *env);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				ft_putstr(char *str);
#endif
