/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:44:44 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/23 11:44:58 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

int		ft_export(t_fd *fd, t_parsing *alk)
{
	int len;
	t_env *save;
	
	save = g_env_list;
	if (alk->param[0] != '\0')
		ft_lstadd_back(&g_env_list, ft_new_env(alk->param));
	else
	{
		while (g_env_list)
			{
				len = ft_strlen(g_env_list->ref);
				if (g_env_list->ref[0] != '\0')
				{
					write(fd->out, "declare -x ", 11);
					write(fd->out, g_env_list->ref, len);
					write(fd->out, "\n", 1);
				}
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
	while((res = ft_strcmp(g_env_list->key, alk->param)) != 0 && g_env_list->next)
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
