/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:04 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/30 15:40:12 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

int		ft_env_display(t_fd *fd)
{
	t_env *save;
	int len;

	save = g_env_list;
	while (g_env_list)
	{
		len = ft_strlen(g_env_list->ref);
		if (g_env_list->ref[0] != '\0')
		{
			write(fd->out, g_env_list->ref, len);
			write(fd->out, "\n", 1);
		}
		g_env_list = g_env_list->next;
	}
	g_env_list = save;
	return (0);
}

int		ft_echo(t_parsing *alk, t_fd *fd)
{
	int len;
	char *buf;
	if (fd->out == -1)
		return (-1);
	
	len = ft_strlen(alk->param);
	if (!(buf = malloc(sizeof(char) * len + 1)))
		return (-1);
	if (fd->in == 0)
		write(fd->out, alk->param, len);
	if (alk->echo_option == FALSE)
		write(fd->out, "\n", 1);
	return (0);
}

int		ft_cd(t_parsing *alk)
{
	int		ret;

	if (!alk->param)
		return (-1);
	alk->param = ft_whitespace(alk->param);
	if (alk->param[0] == '.' && alk->param[1] == '.')
		ft_up_directory(alk);
	if (alk->param[0] == '\0' || alk->param[0] == '~')
		ft_home(alk);
	ret = chdir(alk->param);
	return (ret);
}

int		ft_pwd(t_fd *fd)
{
	char	*buf;
	int		len;

	if (fd->out == -1)
		return (-1);
	if (!(buf = malloc(sizeof(char) * 1024)))
		return (-1);
	getcwd(buf, 1024);
	len = ft_strlen(buf);
	write(fd->out, buf, len);
	free(buf);
	return (0);
}

void	ft_exit(void)
{
	write(1, "exit\n", 5);
	exit(1);
}
