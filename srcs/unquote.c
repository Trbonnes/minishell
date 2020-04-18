/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:40:16 by trombone          #+#    #+#             */
/*   Updated: 2020/04/18 16:06:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

static size_t	ft_strlen_quote_loop(const char *str, size_t len, int builtin_detected)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && str[i + 1] && (builtin_detected != 7 || (builtin_detected == 7 && str[i + 1] != 34)))
		{
			len--;
			while (str[i] && str[++i] != 34)
				;
			len--;
			i++;
		}
		else if (str[i] == 39 && str[i + 1] && (builtin_detected != 7 || (builtin_detected == 7 && str[i + 1] != 39)))
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

static size_t	ft_strlen_quote(const char *str, int builtin_detected)
{
	size_t len;

	len = ft_strlen(str);
	return (ft_strlen_quote_loop(str, len, builtin_detected));
}

static void		ft_strdup_quote(const char *str, char *copy, int builtin_detected)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 && str[i + 1] && (builtin_detected != 7 || (builtin_detected == 7 && str[i + 1] != 34)))
		{
			while (str[i] && str[++i] != 34)
				copy[j++] = str[i];
			i++;
		}
		else if (str[i] == 39 && str[i + 1] && (builtin_detected != 7 || (builtin_detected == 7 && str[i + 1] != 39)))
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

void			ft_unquote(char **str, int builtin_detected)
{
	char *copy;

	if (!(copy = malloc(sizeof(char) * ft_strlen_quote(str[0], builtin_detected) + 1)))
		return ;
	ft_strdup_quote(str[0], copy, builtin_detected);
	free(str[0]);
	str[0] = ft_strdup(copy);
	free(copy);
}
