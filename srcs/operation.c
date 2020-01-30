/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/30 15:56:19 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		superior(t_parsing *alk, int dbchevron, t_fd *fd)
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
	if (fd->out == -1)
	{
		ft_putstr(strerror(errno));
		return (-1);
	}
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] != '\0')
		open_file(alk, fd);
	return (0);
}

int		inferior(t_parsing *alk, int dbchevron, t_fd *fd)
{
	char *fd_open;

	alk->redirection = skip_operation(alk->redirection);
	alk->redirection = ft_whitespace(alk->redirection);
	fd_open = file_name(alk->redirection);
	alk->redirection = skip_file(alk->redirection);
	if (fd->in != 0)
		close(fd->in);
	if (dbchevron == 0)
		fd->in = open(fd_open, O_RDONLY | O_APPEND);
	free(fd_open);
	if (fd->in == -1)
	{
		ft_putstr(strerror(errno));
		return (-1);
	}
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] != '\0')
		open_file(alk, fd);
	return (0);
}

int		find_fd(t_parsing *alk, char **env)
{
	t_fd fd = (t_fd){ 0 };
	int pipe_fd[2];
	t_parsing *tmp;

	tmp = alk;
	while (alk)
	{
		fd.in = 0;
		fd.out = 1;
		if (alk->next)
		{
			pipe(pipe_fd);
			fd.in = pipe_fd[0];
			fd.out = pipe_fd[1];
		}
		if (open_file(alk, &fd) == -1)
			return (0);
		if (alk->builtin_detected == 7)
		{
			if (ft_executable(alk, env, & fd) == -1)
			{
				write(2, "minishell: command not found\n", 29);
				return (-1);
			}
		}
		else
		{
			if (alk->builtin_detected == 0)
				ft_cd(alk);	
			if (alk->builtin_detected == 1)
				ft_echo(alk, &fd);
			if (alk->builtin_detected == 2)
				ft_env_display(&fd);
			if (alk->builtin_detected == 3)
				ft_exit();
			if (alk->builtin_detected == 4)
				ft_export(&fd, alk);
			if (alk->builtin_detected == 5)
				ft_pwd(&fd);
			if (alk->builtin_detected == 6)
				ft_unset(alk);
		}
		if (fd.out != 1)
			close(fd.out);
		if (fd.in != 0)
			close(fd.in);
		alk = alk->next;
	}
	alk = tmp;
	return (0);
}
