/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:54:45 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/17 06:44:37 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;

char	*ft_find_home(void)
{
	int		i;
	char	*path;
	t_env	*tmp;

	tmp = g_env_list;
	i = 0;
	while (g_env_list && ft_strcmp("HOME", g_env_list->key) != 0)
		g_env_list = g_env_list->next;
	if (!g_env_list)
	{
		write(1, "bash: cd: HOME not set\n", 23);
		g_env_list = tmp;
		return (NULL);
	}
	while (g_env_list->ref[i] != '=')
		i++;
	path = ft_strdup(g_env_list->ref + i + 1);
	g_env_list = tmp;
	return (path);
}

int		ft_up_directory(t_parsing *alk)
{
	char	*buf;
	int		i;
	char	*afree;

	afree = alk->param;
	i = 0;
	if (!(buf = malloc(sizeof(char) * 1024)))
		return (-1);
	getcwd(buf, 1024);
	while (buf[i])
		i++;
	if (i > 0)
		i--;
	if (buf[i] == '/' && i > 0)
		i--;
	while (buf[i] != '/' && i > 0)
		i--;
	if (i == 0)
		alk->param = ft_substr(buf, 0, 1);
	else
		alk->param = ft_substr(buf, 0, i);
	free(buf);
	free(afree);
	return (0);
}

void	ft_home(t_parsing *alk)
{
	char	*users;
	char	*afree;
	int		boo;

	boo = 0;
	if (!(users = ft_find_home()))
		boo = 1;
	afree = alk->param;
	if (boo == 0)
	{
		alk->param = ft_strdup(users);
		free(afree);
		free(users);
	}
}
