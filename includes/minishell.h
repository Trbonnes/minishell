/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:31:36 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/21 17:53:23 by trbonnes         ###   ########.fr       */
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

#endif