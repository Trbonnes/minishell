/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 19:32:24 by user42            #+#    #+#             */
/*   Updated: 2020/05/09 13:56:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

int		cd_cd(t_parsing *alk)
{
	char **param;

	param = ft_split(alk->param, '\'', "");
	if (param[1] == 0)
		;
	else if (param[1][0] == 26)
		return (ft_free_params(param, -1));
	else if (param[2] != 0)
		return (ft_free_params(param, error_multi_cd()));
	if (param[1] != 0)
	{
		free(alk->param);
		alk->param = ft_strdup(param[1]);
	}
	ft_free_params(param, 0);
	return (0);
}

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
	while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ';'
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

char	*ft_dollar_call_ret(char *parsed, char *env_check)
{
	t_env	*search;
	char	*parsed_cpy;

	search = g_env_list;
	while (search && ft_strcmp(env_check, search->key) != 0)
		search = search->next;
	if (search != NULL && env_check[0] != '\0')
		return (parsed_cpy = ft_replace_env(search, parsed));
	else
		return (parsed_cpy = ft_delete_dollar(parsed));
}
