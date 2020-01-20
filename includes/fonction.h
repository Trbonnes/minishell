/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:19 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/20 10:51:48 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONCTION_H
# define FONCTION_H
# include "minishell.h"
# define TRUE 1
# define FALSE 0

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_whitespace(char *str);
char	*ft_strjoin(const char *s1, char *s2);

char	*ft_home(char *str);

int		ft_cd(char *str);
int		ft_echo(char *str, int end_fd, int bool);
int		ft_pwd(int fd);

int		find_fd(t_parsing *alk);

int		open_echo(char *str, int fd);

#endif 