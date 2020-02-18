/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:38:43 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/18 09:13:48 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env	*g_env_list;
extern pid_t	g_pid;
static int		g_status;

void	ft_close_redirect_pipe(t_parsing *alk, t_fd *fd)
{
	fd->last_pipe[0] = fd->pipe[0];
	fd->last_pipe[1] = fd->pipe[1];
	if (alk->next)
		pipe(fd->pipe);
	if (!fd->index)
		fd->out = fd->pipe[1];
	if (fd->index && alk->next)
	{
		fd->in = fd->last_pipe[0];
		fd->out = fd->pipe[1];
	}
	if (fd->index && !alk->next)
	{
		fd->in = fd->last_pipe[0];
		fd->out = 1;
	}
	if (fd->index && alk->next)
		close(fd->last_pipe[1]);
	if (fd->index && !alk->next)
		close(fd->last_pipe[1]);
}

void	list_builtin(t_parsing *alk, t_fd *fd)
{
	if (alk->builtin_detected == 0)
		ft_cd(alk);
	if (alk->builtin_detected == 1)
		ft_echo(alk, fd);
	if (alk->builtin_detected == 2)
		ft_env_display(fd);
	if (alk->builtin_detected == 3)
		ft_exit();
	if (alk->builtin_detected == 4)
		ft_export(fd, alk);
	if (alk->builtin_detected == 5)
		ft_pwd(fd);
	if (alk->builtin_detected == 6)
		ft_unset(alk);
}

int		ft_pipe(t_parsing *alk, t_fd *fd, char **env)
{
	t_pid	*jul;

	jul = NULL;
	while (alk)
	{
		ft_close_redirect_pipe(alk, fd);
		if (open_file(alk, fd) == -1)
			return (-1);
		if (alk->builtin_detected == 7)
		{
			g_pid = fork();
			if (g_pid == 0)
				builtin_exec(alk, fd, env);
			else
				ft_pid_back(&jul, ft_newelem(g_pid));
		}
		else
			builtin_exec(alk, fd, env);
		if (fd->index)
			close(fd->last_pipe[0]);
		alk = alk->next;
		fd->index++;
	}
	ft_wait_children(jul);
	return (0);
}

int		builtin_exec(t_parsing *alk, t_fd *fd, char **env)
{
	if (alk->builtin_detected == 7)
	{
		if (!fd->index)
			close(fd->pipe[0]);
		if (fd->index && alk->next)
		{
			close(fd->last_pipe[1]);
			close(fd->pipe[0]);
		}
		if (fd->index && !alk->next)
			close(fd->last_pipe[1]);
		if (ft_executable(alk, env, fd) == -1)
		{
			write(2, "minishell: command not found\n", 29);
			exit(127);
			return (-1);
		}
		if (fd->index && !alk->next)
			close(fd->last_pipe[0]);
	}
	else
		list_builtin(alk, fd);
	return (0);
}

int		builtin_exec_simple(t_parsing *alk, t_fd *fd, char **env)
{
	if (alk->builtin_detected == 7)
	{
		g_pid = fork();
		wait(&g_status);
		g_last_return_value = last_return_setup(g_status);
		if (g_pid == 0)
			if (ft_executable(alk, env, fd) == -1)
			{
				write(2, "minishell: command not found\n", 29);
				exit(127);
				return (-1);
			}
	}
	else
		list_builtin(alk, fd);
	return (0);
}
