/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:54:48 by trostan           #+#    #+#             */
/*   Updated: 2020/04/27 23:59:40 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

void	ft_export_multi(t_parsing *alk)
{
	int		i;
	int		j;
	char	*exp;

	i = 0;
	j = 0;
	while (alk->param[i])
	{
		while (alk->param[i] != '=' && alk->param[i])
			i++;
		while (alk->param[i] != '\0' && alk->param[i] != ' ')
			i++;
		exp = ft_substr(alk->param, j, i - j);
		ft_same_export(exp);
		if (alk->param[0] != '\0')
			ft_lstadd_back(&g_env_list, ft_new_env(exp));
		while (alk->param[i] != '\0' && alk->param[i] == ' ')
			i++;
		j = i;
		free(exp);
	}
}
