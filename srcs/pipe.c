/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:38:43 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/13 05:59:36 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;
extern pid_t	g_pid;
static int		g_status;

int		ft_pipe(t_parsing *alk, t_fd *fd, char **env)
{
	while (alk)
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
		printf("index = %d\n", fd->index);
		if (fd->index && alk->next)
		{
			close(fd->last_pipe[1]);
			printf("close(%d)\n", fd->last_pipe[1]);
		}
		if (fd->index && !alk->next)
		{
			close(fd->last_pipe[1]);
			printf("close(%d)\n", fd->last_pipe[1]);
		}
		printf("pipe[0] = %d pipe[1] = %d\nfd->in = %d fd->out = %d\n", fd->pipe[0], fd->pipe[1], fd->in, fd->out);
		g_pid = fork();
		if (g_pid == 0)
			builtin_exec(alk, fd, env);
		if (fd->index)
		{
			close(fd->last_pipe[0]);
			printf("close(%d)\n", fd->last_pipe[0]);
		}
		alk = alk->next;
		fd->index++;
	}
	wait(&g_status);
	return (0);
}

int		builtin_exec(t_parsing *alk, t_fd *fd, char **env)
{
	if (alk->builtin_detected == 7)
	{
		if (ft_executable(alk, env, fd) == -1)
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
	return (0);
}

int		builtin_exec_simple(t_parsing *alk, t_fd *fd, char **env)
{
	if (alk->builtin_detected == 7)
	{
		g_pid = fork();
		wait(&g_status);
		if (g_pid == 0)
			if (ft_executable(alk, env, fd) == -1)
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
	return (0);
}
