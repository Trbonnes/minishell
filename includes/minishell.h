/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:31:36 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 12:20:34 by trbonnes         ###   ########.fr       */
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
# include <stdio.h> // a enlever

typedef struct		s_env
{
	char			*key;
	char			*ref;
	struct s_env	*next;
}					t_env;
typedef struct		s_parsing
{
	int				builtin_detected;
	int				echo_option;
	char			*param;
	char			*redirection;
}					t_parsing;

int 	ft_detect_builtin();
int		ft_tolower(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, char *s2);
char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	ft_envdelone(t_env *lst);
void	ft_envclear(t_env **lst);
char	*ft_strdup_chr(const char *str, char c);
size_t	ft_strlen_chr(const char *str, char c);
int		ft_wait_quote(char **str, char c);
int		ft_redirection_calculate(int i, char **str);
void	ft_unquote(char **str);

#endif