/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 09:24:44 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/17 09:04:18 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

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

char		**ft_argnumber(int *count, int *i, char const *cmd)
{
	char **split;

	*count += 1;
	*i = -1;
	if (!(split = malloc(sizeof(char*) * (*count + 1))))
		return (NULL);
	if (*i == -1)
	{
		if (!(split[0] = ft_strdup(cmd)))
			return (NULL);
		*i = 1;
	}
	return (split);
}

char		**ft_split(char const *str, char c, char const *cmd)
{
	char	**split;
	int		count;
	int		s;
	int		i;
	int		j;

	i = 0;
	s = 0;
	count = ft_count(str, c);
	if (count == 0)
		return (ft_no_args());
	split = ft_argnumber(&count, &i, cmd);
	while (i < count && str[s])
	{
		s = ft_next(str, c, s);
		j = 0;
		if (!(split[i] = malloc(sizeof(char) * (ft_length(str, c, s) + 1))))
			return (NULL);
		while (str[s] != c && str[s])
			split[i][j++] = str[s++];
		split[i][j] = '\0';
		i++;
	}
	split[i] = 0;
	return (split);
}
