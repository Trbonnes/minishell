/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:28:05 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:28:06 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_escape_zero(char **str, char *tmp, int *i, int *j)
{
	if (str[0][i[0] + 1] == '\0')
		tmp[j[0]++] = str[0][i[0]];
	else
	{
		tmp[j[0]++] = 26;
		tmp[j[0]++] = str[0][++i[0]];
		tmp[j[0]++] = 26;
	}
}

void	ft_escape_quote(char **str, char *tmp, int *i, int *j)
{
	tmp[j[0]++] = str[0][i[0]++];
	tmp[j[0]++] = str[0][i[0]];
}

char	**ft_replace_quote_split(char **split)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == 31)
				split[i][j] = '\'';
			j++;
		}
		i++;
	}
	return (split);
}

void	ft_replace_quote_string(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == 31)
			str[i] = '\'';
}
