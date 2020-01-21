/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:19 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/21 18:28:26 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONCTION_H
# define FONCTION_H
# include "minishell.h"
# define TRUE 1
# define FALSE 0

typedef	struct	s_fd
{
	int in;
	int out;
}				t_fd;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_whitespace(char *str);
char	*ft_strjoin(const char *s1, char *s2);

void	ft_home(t_parsing *alk);

int		ft_cd(t_parsing *alk);
int		ft_echo(t_parsing *alk, t_fd *fd);
int		ft_pwd(t_fd *fd);

int		find_fd(t_parsing *alk);
void	superior(char **str, int dbchevron, t_fd *fd);
void	inferior(char **str, int dbchevron, t_fd *fd);

void	open_file(char *str, t_fd *fd);
char	*skip_file(char *str);
char	*file_name(char *str);
char	*skip_operation(char *str);
int		strlen_word_file(char *str, int fileorstr);

#endif 