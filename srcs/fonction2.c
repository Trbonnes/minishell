/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:44:44 by trdella-          #+#    #+#             */
/*   Updated: 2020/05/09 11:40:58 by trostan          ###   ########.fr       */
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

	cpy = lst_cpy();
	save = cpy;
	printf("par = {%s}\n", alk->param);
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

	i = 0;
	j = 0;
	save = g_env_list;
	if (alk->param[0] == '\0')
		return (0);
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
