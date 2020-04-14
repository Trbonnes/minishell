/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:40:16 by trombone          #+#    #+#             */
/*   Updated: 2020/04/14 15:37:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

static size_t	ft_strlen_quote_loop(const char *str, size_t len)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && str[i + 1])
		{
			len--;
			while (str[i] && str[++i] != 34)
				;
			len--;
			i++;
		}
		else if (str[i] == 39 && str[i + 1])
		{
			len--;
			while (str[i] && str[++i] != 39)
				;
			len--;
			i++;
		}
		else
			i++;
	}
	return (len);
}

static size_t	ft_strlen_quote(const char *str)
{
	size_t len;

	len = ft_strlen(str);
	return (ft_strlen_quote_loop(str, len));
}

static void		ft_strdup_quote(const char *str, char *copy)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 && str[i + 1])
		{
			while (str[i] && str[++i] != 34)
				copy[j++] = str[i];
			i++;
		}
		else if (str[i] == 39 && str[i + 1])
		{
			while (str[i] && str[++i] != 39)
				copy[j++] = str[i];
			i++;
		}
		else
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
