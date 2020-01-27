/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 09:24:44 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/27 13:27:42 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static int	ft_next(char const *str, char c, int i)
{
	if (i == 0 && str[i] != c && str[i])
		return (i);
	while (str[i] != c && str[i])
		i++;
	while (str[i] == c && str[i])
		i++;
	return (i);
}

static int	ft_length(char const *str, char c, int i)
{
	int length;

	length = 0;
	while (str[i + length] != c && str[i + length])
		length++;
	return (length);
}

char		**ft_argnumber(int *count, int *i)
{
	char **tab;

	if (*count == 1)
	{
		*count += 1;
		*i = -1;
	}
	if (!(tab = malloc(sizeof(char*) * (*count + 1))))
		return (NULL);
	if (*i == -1)
	{
		if (!(tab[0] = malloc(sizeof(char) * 1)))
			return (NULL);
		tab[0][0] = '\0';
		*i = 1;
	}
	return (tab);
}

char		**ft_split(char const *str, char c)
{
	char	**tab;
	int		count;
	int		s;
	int		i;
	int		j;

	i = 0;
	s = 0;
	count = ft_count(str, c);
	if (count == 0)
		return (ft_no_args());
	tab = ft_argnumber(&count, &i);
	while (i < count && str[s])
	{
		s = ft_next(str, c, s);
		j = 0;
		if (!(tab[i] = malloc(sizeof(char) * (ft_length(str, c, s) + 1))))
			return (NULL);
		while (str[s] != c && str[s])
			tab[i][j++] = str[s++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
	return (tab);
}