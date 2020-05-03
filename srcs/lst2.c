/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:32:24 by user42            #+#    #+#             */
/*   Updated: 2020/05/03 11:59:58 by user42           ###   ########.fr       */
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

t_env	*lst_cpy(void)
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

char	*ft_parser_cmd_full(char *str, char *parsed, int i, int j)
{
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';'
	&& str[i] != '|' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\'')
		{
			parsed[j++] = str[i++];
			while (str[i] && str[i] != '\'')
				parsed[j++] = str[i++];
		}
		if (str[i] == '"')
		{
			parsed[j++] = str[i++];
			while (str[i] && str[i] != '"')
				parsed[j++] = str[i++];
		}
		if (str[i])
			parsed[j++] = str[i++];
	}
	parsed[j] = '\0';
	ft_unquote(&parsed, 0);
	return (parsed);
}
