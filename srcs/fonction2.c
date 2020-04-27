/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:44:44 by trdella-          #+#    #+#             */
/*   Updated: 2020/04/28 01:11:38 by trostan          ###   ########.fr       */
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

void	ft_same_export(char *exp)
{
	t_env		*save;
	t_parsing	key;
	int			i;

	i = 0;
	key = (t_parsing){ 0 };
	while (exp && exp[i] != '=' && exp[0])
		i++;
	if (exp[i])
	{
		if (!(key.param = malloc(sizeof(char) * (i + 1))))
			return ;
		i = 0;
		while (exp && exp[i] != '=')
		{
			key.param[i] = exp[i];
			i++;
		}
		key.param[i] = '\0';
	}
	save = g_env_list;
	ft_export_norme(save, &key);
}

int		ft_export(t_fd *fd, t_parsing *alk)
{
	t_env	*cpy;
	t_env	*save;

	printf("param = %s\n", alk->param);
	cpy = lst_cpy();
	save = cpy;
	ft_export_multi(alk);
	if (alk->param[0] == '\0')
	{
		sort_list(&cpy);
		while (cpy)
		{
			ft_export_loop(fd, cpy);
			cpy = cpy->next;
		}
	}
	cpy = save;
	ft_clear_cpy(cpy);
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
