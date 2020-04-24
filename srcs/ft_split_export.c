/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 17:18:21 by user42            #+#    #+#             */
/*   Updated: 2020/04/24 19:30:18 by user42           ###   ########.fr       */
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
		while (str[i] && str[i] != '=' && str[i] != ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' && i++)
				while (str[i] && str[i] != '\'')
					i++;
			else if (str[i] == '\"' && i++)
				while (str[i] && str[i] != '\"')
					i++;
			else if (str[i])
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
		while (str[i] && str[i] != '=' && str[i] != ' ')
		{
			i++;
			len[j]++;
		}
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' && i++ && len[j]++)
				while (str[i] && str[i] != '\'')
				{
					i++;
					len[j]++;
				}
			else if (str[i] == '\"' && i++ && len[j]++)
				while (str[i] && str[i] != '\"')
				{
					i++;
					len[j]++;
				}
			else if (str[i])
			{
				len[j]++;
				i++;
			}
		}
		if (str[i])
		{
			i++;
			j++;
		}
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
	j = 0;
	while (j < i)
	{
		k = 0;
		if (!(split[j] = malloc(sizeof(char) * len[j] + 1)))
			return (NULL);
		while (k < len[j])
			split[j][k++] = *str++;
		split[j][k] = '\0';
		str++;
		j++;
	}
	split[j] = 0;
	free(len);
	return (split);
}