/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:32:24 by user42            #+#    #+#             */
/*   Updated: 2020/04/28 00:15:15 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

void	ft_clear_cpy(t_env *lst)
{
	t_env *tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->key);
		free(lst->ref);
		lst = lst->next;
		free(tmp);
	}
}

t_env	*lst_cpy()
{
	t_env	*save;
	t_env	*tmp;
	t_env	*lst;
	
	if (!(lst = malloc(sizeof(t_env))))
		return (NULL);
	tmp = lst;
	save = g_env_list;
	while (g_env_list)
	{
		lst->key = ft_strdup(g_env_list->key);
		lst->ref = ft_strdup(g_env_list->ref);
		if (g_env_list->next)
		{
			if (!(lst->next = malloc(sizeof(t_env))))
				return (NULL);
			lst = lst->next;
		}
		else
			lst->next = NULL;
		g_env_list = g_env_list->next;
	}
	g_env_list = save;
	lst = tmp;
	return (lst);
}