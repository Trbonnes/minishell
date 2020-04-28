/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:54:48 by trostan           #+#    #+#             */
/*   Updated: 2020/04/28 14:56:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

void	ft_export_multi(t_parsing *alk)
{
	int		i;
	char	**split;

	i = 0;
	split = check_param_env(alk);
	while (split[i])
	{
		ft_same_export(split[i]);
		if (split[i][0] != '\0')
			ft_lstadd_back(&g_env_list, ft_new_env(split[i]));
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_unset_multiple(char *uns)
{
	int		res;
	t_env	*tmp_free;

	while ((res = ft_strcmp(g_env_list->key, uns)) != 0
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
}

char	**check_param_env(t_parsing *alk)
{
	char	**strings;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strings = ft_split_export(alk->param);
	while (strings[i])
		i++;
	while (j < i)
	{
		ft_unquote(&strings[j], 2);
		j++;
	}
	j = 0;
	while (j < i)
		j++;
	return (strings);
}

void	env_multiple(char **string, t_fd *fd)
{
	int i;

	i = 0;
	while (string[i])
	{
		write(fd->out, string[i], ft_strlen(string[i]));
		write(fd->out, "\n", 1);
		i++;
	}
	i = 0;
	while (string[i])
		free(string[i++]);
	free(string);
}
