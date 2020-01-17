/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:31:36 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/17 14:45:32 by trbonnes         ###   ########.fr       */
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

typedef struct	s_parsing
{
	int builtin_detected;
	int option;
	int sep;
	char *param;
}				t_parsing;

int ft_detect_builtin();
int	ft_tolower(int c);
int	ft_strcmp(const char *s1, const char *s2);

#endif