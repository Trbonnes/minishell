/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/22 11:36:29 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	superior(t_parsing *alk, int dbchevron, t_fd *fd)
{
	char *fd_open;

	alk->redirection = skip_operation(alk->redirection);
	alk->redirection = ft_whitespace(alk->redirection);
	fd_open = file_name(alk->redirection);
	alk->redirection = skip_file(alk->redirection);
	if (fd->out != 1)
		close(fd->out);
	if (dbchevron == 0)
		fd->out = open(fd_open, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else
		fd->out = open(fd_open, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	free(fd_open);
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] != '\0')
		open_file(alk, fd);
}

void	inferior(t_parsing *alk, int dbchevron, t_fd *fd)
{
	char *fd_open;

	alk->redirection = skip_operation(alk->redirection);
	alk->redirection = ft_whitespace(alk->redirection);
	fd_open = file_name(alk->redirection);
	alk->redirection = skip_file(alk->redirection);
	if (fd->in != 0)
		close(fd->in);
	if (dbchevron == 0)
		fd->in = open(fd_open, O_RDONLY | O_APPEND | O_CREAT, S_IRWXU);
	free(fd_open);
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] != '\0')
		open_file(alk, fd);
}

int		find_fd(t_parsing *alk)
{
	t_fd fd;

	fd.in = 0;
	fd.out = 1;
	write(1,"\n", 1);
	open_file(alk, &fd);
	if (alk->builtin_detected == 0)
		ft_cd(alk);
	if (alk->builtin_detected == 1)
		ft_echo(alk, &fd);
	if (alk->builtin_detected == 3)
		ft_exit();
	if (alk->builtin_detected == 5)
		ft_pwd(&fd);
	if (fd.out != 1)
		close(fd.out);
	if (fd.in != 0)
		close(fd.in);
		printf("\n");
	return (0);
}
