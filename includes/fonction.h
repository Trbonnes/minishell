/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:19 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/27 13:08:37 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONCTION_H
# define FONCTION_H
# include "minishell.h"
# include <string.h>
# include <errno.h>
# define TRUE 1
# define FALSE 0

typedef	struct	s_fd
{
	int			in;
	int			out;
	int			pipe_b;
	int			pipe[2];
}				t_fd;

size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_whitespace(char *str);
char			*ft_strjoin(const char *s1, char *s2);

void			ft_home(t_parsing *alk);
int				ft_up_directory(t_parsing *alk);

int				ft_cd(t_parsing *alk);
int				ft_echo(t_parsing *alk, t_fd *fd);
int				ft_pwd(t_fd *fd);
void			ft_exit(void);
int				ft_env_display(t_fd *fd);

int				ft_export(t_fd *fd, t_parsing *alk);
int				ft_unset(t_parsing *alk);

int				find_fd(t_parsing *alk);
int				superior(t_parsing *alk, int dbchevron, t_fd *fd);
int				inferior(t_parsing *alk, int dbchevron, t_fd *fd);

int				open_file(t_parsing *alk, t_fd *fd);
char			*skip_file(char *str);
char			*file_name(char *str);
char			*skip_operation(char *str);
int				strlen_word_file(char *str);

t_env			*ft_new_env(char *env);
void			ft_lstadd_back(t_env **lst, t_env *new);
void			ft_putstr(char *str);

#endif
