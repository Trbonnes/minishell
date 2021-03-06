/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:30:48 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:30:48 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_split_export_nb(char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' && ++i)
				while (str[i] && str[i] != '\'')
					i++;
			else if (str[i] == '"' && ++i)
				while (str[i] && str[i] != '"')
					i++;
			if (str[i])
				i++;
		}
		nb++;
		if (str[i])
			i++;
	}
	return (nb);
}

int		*ft_split_export_len(char *str, int i)
{
	int		*len;
	int		j;

	j = 0;
	if (!(len = malloc(sizeof(int) * i)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		len[j] = 0;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' && ++i && ++len[j])
				while (str[i] && str[i] != '\'' && ++i)
					len[j]++;
			else if (str[i] == '\"' && ++i && ++len[j])
				while (str[i] && str[i] != '\"' && ++i)
					len[j]++;
			if (str[i] && ++i)
				len[j]++;
		}
		if (str[i] && ++i)
			j++;
	}
	return (len);
}

char	**ft_split_export(char *str)
{
	int		i;
	int		j;
	int		k;
	int		*len;
	char	**split;

	if ((i = ft_split_export_nb(str)) == -1)
		return (NULL);
	len = ft_split_export_len(str, i);
	if (!(split = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	j = -1;
	while (++j < i)
	{
		k = 0;
		if (!(split[j] = malloc(sizeof(char) * len[j] + 1)))
			return (NULL);
		while (k < len[j])
			split[j][k++] = *str++;
		split[j][k] = '\0';
		str++;
	}
	split[j] = 0;
	free(len);
	return (ft_replace_quote_split(split));
}
