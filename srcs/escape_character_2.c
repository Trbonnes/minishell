/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escapa_character_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:10:48 by user42            #+#    #+#             */
/*   Updated: 2020/05/10 15:20:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_escape_zero(char **str, char *tmp, int *i, int *j)
{
	if (str[0][i[0] + 1] == '\0'
	|| str[0][i[0] + 1] == ' ' || str[0][i[0] + 1] == '	')
		tmp[j[0]++] = str[0][i[0]];
	else
	{
		tmp[j[0]++] = '\'';
		tmp[j[0]++] = str[0][++i[0]];
		tmp[j[0]++] = '\'';
	}
}

void	ft_escape_quote(char **str, char *tmp, int *i, int *j)
{
	tmp[j[0]++] = str[0][i[0]++];
	tmp[j[0]++] = str[0][i[0]];
}
