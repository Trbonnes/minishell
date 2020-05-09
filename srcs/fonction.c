/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:04 by trdella-          #+#    #+#             */
/*   Updated: 2020/05/09 13:15:34 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env *g_env_list;

int		ft_env_display(t_fd *fd, t_parsing *alk)
{
	t_env	*save;
	int		len;
	char	**string;

	save = g_env_list;
	if (alk->param[0] != '\0')
		string = check_param_env(alk);
	while (g_env_list)
	{
		len = ft_strlen(g_env_list->ref);
		if (g_env_list->ref[0] != '\0' &&
		ft_strcmp(g_env_list->key, g_env_list->ref) != 0)
		{
			write(fd->out, g_env_list->ref, len);
			write(fd->out, "\n", 1);
		}
		g_env_list = g_env_list->next;
	}
	if (alk->param[0] != '\0')
		env_multiple(string, fd);
	g_env_list = save;
	return (0);
}

int		ft_echo(t_parsing *alk, t_fd *fd)
{
	int len;

	if (fd->out == -1)
		return (1);
	len = ft_strlen(alk->param);
	write(fd->out, alk->param, len);
	if (alk->echo_option == FALSE)
		write(fd->out, "\n", 1);
	return (0);
}

int		ft_cd(t_parsing *alk)
{
	int			i;
	t_parsing	test;
	char		**cmd;
	char		save[1024];

	if (cd_cd(alk) == -1)
		return (0);
	i = ft_cd_2(save, alk);
	cmd = ft_split(alk->param, '/', "/");
	if (alk->param[0] == '/')
		free(cmd[0]);
	if (alk->param[0] == '/')
		cmd[0] = ft_strdup("/");
	while (cmd[++i])
	{
		test.param = ft_strdup(cmd[i]);
		if (ft_cd_multi(&test) == -1 || alk->index)
		{
			free(test.param);
			chdir(save);
			return (ft_free_params(cmd, 1));
		}
		free(test.param);
	}
	return (ft_free_params(cmd, 0));
}

int		ft_pwd(t_fd *fd)
{
	char	*buf;
	int		len;

	if (fd->out == -1)
		return (1);
	if (!(buf = malloc(sizeof(char) * 1024)))
		return (-1);
	getcwd(buf, 1024);
	len = ft_strlen(buf);
	write(fd->out, buf, len);
	write(fd->out, "\n", 1);
	free(buf);
	return (0);
}

void	ft_exit(t_parsing *alk)
{
	write(1, "exit\n", 5);
	exit(ft_atoi(alk->param));
}
