/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/21 16:35:59 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	superior(char **str, int dbchevron, t_fd *fd)
{
	char *fd_open;

	*str = skip_operation(*str);
	*str = ft_whitespace(*str);
	fd_open = file_name(*str);
	*str = skip_file(*str);
	if (fd->out != 1)
		close(fd->out);
	if (dbchevron == 0)
		fd->out = open(fd_open, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else
		fd->out = open(fd_open, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	free(fd_open);
	*str = ft_whitespace(*str);
	if (*str[0] != '\0')
		open_file(*str, fd);
}

void	inferior(char **str, int dbchevron, t_fd *fd)
{
	char *fd_open;

	*str = skip_operation(*str);
	*str = ft_whitespace(*str);
	fd_open = file_name(*str);
	*str = skip_file(*str);
	if (fd->in != 0)
		close(fd->in);
	if (dbchevron == 0)
		fd->in = open(fd_open, O_RDONLY | O_APPEND | O_CREAT, S_IRWXU);
	free(fd_open);
	*str = ft_whitespace(*str);
	if (*str[0] != '\0')
		open_file(*str, fd);
}

int		find_fd(t_parsing *alk)
{
	t_fd fd;

	fd.in = 0;
	fd.out = 1;
	open_file(alk->redirection, &fd);
	if (alk->builtin_detected == 0)
		ft_cd(alk->redirection);
	if (alk->builtin_detected == 1)
		ft_echo(alk->param, &fd, alk->echo_option);
	if (fd.out != 1)
		close(fd.out);
	if (fd.in != 0)
		close(fd.in);
	return (0);
}
