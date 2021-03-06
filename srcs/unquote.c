/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:33:57 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:33:57 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void		ft_str_dup_dup(const char *str, char *copy, int *i, int *j)
{
	if (str[(*i)] == 34 && str[(*i)] && str[(*i) + 1]
	&& ((*i) == 0 || str[(*i) - 1] != '\\'))
	{
		while (str[(*i)] && str[++(*i)] != 34)
			if (str[(*i)])
				copy[(*j)++] = str[(*i)];
		if (str[(*i)])
			(*i)++;
	}
	else if (str[(*i)] == 39 && str[(*i)] && str[(*i) + 1]
	&& ((*i) == 0 || str[(*i) - 1] != '\\'))
	{
		while (str[(*i)] && str[++(*i)] != 39)
			if (str[(*i)])
				copy[(*j)++] = str[(*i)];
		if (str[(*i)])
			(*i)++;
	}
	else if (str[(*i)])
		copy[(*j)++] = str[(*i)++];
}

void		ft_strdup_quote(const char *str, char *copy,
int builtin_detected)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (builtin_detected == 6
		&& str[i] && str[i] == 34 && str[i + 1] == 34)
		{
			copy[j++] = str[i++];
			copy[j++] = str[i++];
		}
		if (builtin_detected == 6
		&& str[i] && str[i] == 39 && str[i + 1] == 39)
		{
			copy[j++] = str[i++];
			copy[j++] = str[i++];
		}
		ft_str_dup_dup(str, copy, &i, &j);
	}
	copy[j] = '\0';
}

void		ft_unquote(char **str, int builtin_detected)
{
	char *copy;

	if (!(copy = malloc(sizeof(char) * ft_strlen_quote(str[0],
	builtin_detected) + 1)))
		return ;
	ft_strdup_quote(str[0], copy, builtin_detected);
	free(str[0]);
	str[0] = ft_strdup(copy);
	free(copy);
}
