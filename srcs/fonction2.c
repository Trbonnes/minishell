/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:44:44 by trdella-          #+#    #+#             */
/*   Updated: 2020/03/10 21:59:09 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env *g_env_list;

void	ft_export_norme(t_env *save, t_parsing *key)
{
	if (key->param)
	{
		while (save && ft_strcmp(key->param, save->key) != 0)
			save = save->next;
		ft_unset(key);
		free(key->param);
	}
}

void	ft_same_export(t_parsing *alk)
{
	t_env		*save;
	t_parsing	key;
	int			i;

	i = 0;
	key = (t_parsing){ 0 };
	while (alk->param && alk->param[i] != '=' && alk->param[0])
		i++;
	if (alk->param[i])
	{
		if (!(key.param = malloc(sizeof(char) * (i + 1))))
			return ;
		i = 0;
		while (alk->param && alk->param[i] != '=')
		{
			key.param[i] = alk->param[i];
			i++;
		}
		key.param[i] = '\0';
	}
	save = g_env_list;
	ft_export_norme(save, &key);
}

int		ft_export(t_fd *fd, t_parsing *alk)
{
	t_env	*save;
	int		i;

	i = 0;
	while (alk->param[i] != '=' && alk->param[i])
		i++;
	if (alk->param[i] == '\0' && i != 0)
		return (0);
	save = g_env_list;
	ft_same_export(alk);
	if (alk->param[0] != '\0')
		ft_lstadd_back(&g_env_list, ft_new_env(alk->param));
	else
	{
		while (g_env_list)
		{
			ft_export_loop(fd, g_env_list);
			g_env_list = g_env_list->next;
		}
	}
	g_env_list = save;
	return (0);
}

int		ft_unset(t_parsing *alk)
{
	t_env	*save;
	t_env	*tmp_free;
	int		res;

	save = g_env_list;
	if (alk->param[0] == '\0')
		return (0);
	while ((res = ft_strcmp(g_env_list->key, alk->param)) != 0
	&& g_env_list->next)
	{
		tmp_free = g_env_list;
		g_env_list = g_env_list->next;
	}
	if (res == 0)
	{
		tmp_free->next = g_env_list->next;
		ft_envdelone(g_env_list);
	}
	g_env_list = save;
	return (0);
}
