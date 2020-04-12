/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trombone <trombone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:40:16 by trombone          #+#    #+#             */
/*   Updated: 2020/04/12 16:00:34 by trombone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

static size_t	ft_strlen_quote(const char *str)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == 34)
		{
			len--;
			while (str[++i] != 34)
				;
			len--;
		}
		i++;
		if (str[i] == 39)
		{
			len--;
			while (str[++i] != 39)
				;
			len--;
		}
		i++;
	}
	return (len);
}

static void		ft_strdup_quote(const char *str, char *copy)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			while (str[++i] != 34)
				copy[j++] = str[i];
			i++;
		}
		if (str[i] == 39)
		{
			while (str[++i] != 39)
				copy[j++] = str[i];
			i++;
		}
		copy[j++] = str[i++];
	}
	copy[j] = '\0';
}

void			ft_unquote(char **str)
{
	char *copy;

	if (!(copy = malloc(sizeof(char) * ft_strlen_quote(str[0]) + 1)))
		return ;
	ft_strdup_quote(str[0], copy);
	free(str[0]);
	str[0] = ft_strdup(copy);
	free(copy);
}
