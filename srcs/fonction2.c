/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:44:44 by trdella-          #+#    #+#             */
/*   Updated: 2020/06/04 05:08:11 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env *g_env_list;

int		ft_export_norme(t_env *save, t_parsing *key, int i)
{
	int val;

	val = 1;
	if (key->param)
	{
		while (save && ft_strcmp(key->param, save->key) != 0)
			save = save->next;
		if (save && key->redirection[i] == '=')
			ft_unset(key);
		if (save && key->redirection[i] != '=')
			val = 0;
		free(key->param);
		free(key->redirection);
	}
	return (val);
}

int		ft_same_export(char *exp)
{
	t_env		*save;
	t_parsing	key;
	int			i;

	i = 0;
	key = (t_parsing){ 0 };
	while (exp && exp[i] && exp[i] != '=' && exp[0])
		i++;
	key.param = ft_substr(exp, 0, i);
	key.redirection = ft_strdup(exp);
	save = g_env_list;
	i = ft_export_norme(save, &key, i);
	return (i);
}

int		ft_export(t_fd *fd, t_parsing *alk)
{
	t_env	*cpy;
	t_env	*save;

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
	if (g_last_return_value == 1)
		return (1);
	return (0);
}

int		ft_unset(t_parsing *alk)
{
	t_env	*save;
	int		i;
	int		j;
	char	*uns;

	j = 0;
	i = 0;
	save = g_env_list;
	if (alk->param[0] == '\0')
		return (0);
	ft_replace_quote_string(alk->param);
	while (alk->param[i])
	{
		while (alk->param[i] != ' ' && alk->param[i])
			i++;
		uns = ft_substr(alk->param, j, i - j);
		ft_unset_multiple(uns);
		if (alk->param[i] != '\0')
			i++;
		j = i;
		g_env_list = save;
		free(uns);
	}
	return (0);
}
