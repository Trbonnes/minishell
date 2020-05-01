/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:19 by trdella-          #+#    #+#             */
/*   Updated: 2020/05/01 03:58:10 by trostan          ###   ########.fr       */
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
# include <sys/wait.h>
# define TRUE 1
# define FALSE 0

typedef	struct		s_fd
{
	int				in;
	int				out;
	int				index;
	int				pipe[2];
	int				last_pipe[2];
}					t_fd;

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
	int					pid;
	struct s_parsing	*next;
}					t_parsing;

typedef struct		s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}					t_pid;

int					ft_detect_builtin(char **env);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin(const char *s1, char *s2);
char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *str);
void				ft_bzero(void *s, size_t n);
void				ft_envdelone(t_env *lst);
void				ft_envclear(t_env **lst);
char				*ft_strdup_chr(const char *str, char c);
size_t				ft_strlen_chr(const char *str, char c);
void				ft_wait_quote(char c, char **quote_str);
int					ft_redirection_calculate(int i, char **str, char **q);
void				ft_unquote(char **str, int builtin_detected);
void				ft_environment_parsing(char **env);
int					ft_redirection_quote(int i, char **str,
char **quote_str, char c);
int					ft_increment_begin(char *str, int i);
int					ft_increment_end(char *str, int i);
int					ft_increment_option(char *str, int i, t_parsing *parser);
int					ft_parser_get(t_parsing *parser, char *str, int i);
char				*ft_parser_param(char *str);
char				*ft_parser_redirection(char **builtin_str,
int builtin_detected);
int					ft_option(char *str, t_parsing *parser, int i);
void				ft_quote_cpy(int i, int j, char **redirection, char **q);
int					ft_quote_check(char c, int quote);
char				*ft_realloc_param_str(int i, int j, char *param_str);
void				ft_parserclear(t_parsing **lst);
char				**ft_split(char const *str, char c, char const *cmd);
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
void				ft_exit(t_parsing *alk);
int					ft_env_display(t_fd *fd, t_parsing *alk);
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
int					builtin_exec_simple(t_parsing *alk, t_fd *fd, char **env);
int					ft_pipe(t_parsing *alk, t_fd *fd, char **env);
int					builtin_exec(t_parsing *alk, t_fd *fd, char **env);
int					ft_free_params(char **params, int ret);
int					ft_selfmade_binary(t_parsing *parser, char **env,
char **params);
int					ft_str_check(char *str);
int					parser_init(char *str, int i, t_parsing **parser,
t_parsing **parser_save);
int					ft_execute_and_clear(t_parsing *parser,
t_parsing *parser_save, char **env);
int					ft_detect_builtin(char **env);
int					ft_select_builtin(char **builtin_str);
int					ft_str_loop(char **env, int i, char *str);
t_pid				*ft_newelem(int pid);
void				ft_lstclear(t_pid	**jul);
void				ft_wait_children(t_pid *jul);
void				ft_pid_back(t_pid **lst, t_pid *new);
char				*ft_no_space(char *str);
char				*ft_dollar_env(char *parsed);
void				ft_export_loop(t_fd *fd, t_env *lst);
char				*ft_itoa(int n);
int					last_return_setup(int status);
int					chevron_error(void);
int					ft_parser_param_quote(char *str, char c);
int					ft_ref_len(t_env *search);
int					ft_find_dollar(char *parsed);
char				*ft_replace_env_loop(t_env *search, char *parsed,
char *parsed_cpy, int k);
int					ft_dollar_env_loop(char *parsed);
int					ft_quote_before_after(const char *str, int i,
int builtin_detected);
size_t				ft_strlen_quote(const char *str, int builtin_detected);
int					error_message_builtin(t_parsing *alk);
int					ft_atoi(const char *nptr);
bool				ft_into_quote(char *parsed, int i, bool into_q);
char				**ft_split_libft(char const *str, char c);
void				ft_quote_executable(char **str);
void				ft_check_split(char **split);
void				display_error_env(int builtin, char *param_str);
int					is_env_var(char c);
int					param_refull_k(t_parsing *alk,
char **split, bool *is_error);
void				ft_list_copy_env(t_env *list);
void				sort_list(t_env **sorted);
t_env				*lst_cpy();
char				**ft_split_export(char *str);
int					check_is_error_env(t_parsing *alk, char **split,
bool *is_error, int i);
void				ft_export_multi(t_parsing *alk);
void				ft_same_export(char *exp);
void				ft_clear_cpy(t_env *lst);
void				ft_unset_multiple(char *uns);
char				**check_param_env(t_parsing *alk);
void				env_multiple(char **string, t_fd *fd);
int					ft_cd_multi(t_parsing *alk);
int					ft_free_tab(char **tabl);
int					ft_cd_2(char *save, t_parsing *alk);
#endif
