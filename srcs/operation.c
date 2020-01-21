/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/21 10:49:22 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"


int		superior(char **str, int dbchevron, int fd)
{
	char *fd_open;
	
	*str = skip_operation(*str);
	*str = ft_whitespace(*str);
	fd_open = file_name(*str);
	*str = skip_file(*str);
	if (dbchevron == 0)
		fd = open(fd_open, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else
		fd = open(fd_open, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	free(fd_open);
	*str = ft_whitespace(*str);
	if (*str[0] != '\0')
	{
		if (*str[0] == '>')
			close(fd);
		fd = open_file(*str, fd);
	}
	else
		return (fd);
	return (fd);
}

int		find_fd(t_parsing *alk)
{
	int fd;
	
	fd = open_file(alk->redirection, 1);
	printf("fd = %d\n",fd);
	if (alk->builtin_detected == 0)
		ft_cd(alk->redirection);
	if (alk->builtin_detected == 1)
		ft_echo(alk->param, fd, alk->echo_option);
	close(fd);
	return (0);
}