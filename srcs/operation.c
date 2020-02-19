/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/19 10:52:04 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern pid_t	g_pid;

void	ft_wait_chevron_2(char *line, t_parsing *alk)
{
	int end;
	int i;

	i = 0;
	end = 0;
	if (alk->redirection[0] == '\0')
		write(2,
		"minishell: syntax error near unexpected token `newline'\n", 56);
	if (alk->redirection[0] == '\0')
		exit(258);
	while (end != 1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &line) > 0 &&
		ft_strcmp(line, alk->redirection) != 0)
		{
			i++;
			free(line);
		}
		else
			end = 1;
	}
	exit(1);
}

void	ft_wait_chevron(t_parsing *alk)
{
	char	*line;
	int		i;
	int		value;
	int		end;

	end = 0;
	g_pid = fork();
	wait(&value);
	g_last_return_value = last_return_setup(value);
	i = 0;
	line = NULL;
	if (g_pid == 0)
		ft_wait_chevron_2(line, alk);
}

int		superior(t_parsing *alk, int dbchevron, t_fd *fd)
{
	char *fd_open;

	alk->redirection = skip_operation(alk->redirection);
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] == '\0')
		return (chevron_error());
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
	if (alk->redirection[0] == '\0')
		return (chevron_error());
	if (dbchevron == 1)
		ft_wait_chevron(alk);
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
	t_fd		fd;
	t_parsing	*tmp;

	fd = (t_fd) { 0 };
	tmp = alk;
	fd.in = 0;
	fd.out = 1;
	if (alk->next)
		ft_pipe(alk, &fd, env);
	else
	{
		if (open_file(alk, &fd) == -1)
			return (0);
		builtin_exec_simple(alk, &fd, env);
	}
	if (fd.out != 1)
		close(fd.out);
	if (fd.in != 0)
		close(fd.in);
	alk = tmp;
	return (0);
}
