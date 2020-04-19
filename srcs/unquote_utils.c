/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 14:16:52 by user42            #+#    #+#             */
/*   Updated: 2020/04/19 14:17:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

size_t	ft_strlen_quote_loop_increment(const char *str, int i,
char c, size_t *len)
{
	*len -= 1;
	while (str[i] && str[++i] != c)
		;
	if (str[i])
	{
		*len -= 1;
		i++;
	}
	return (i);
}

size_t	ft_strlen_quote_loop(const char *str, size_t len,
int builtin_detected)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i = ft_quote_before_after(str, i, builtin_detected);
		if (str[i] == 34 && str[i] && str[i + 1])
			i = ft_strlen_quote_loop_increment(str, i, 34, &len);
		else if (str[i] == 39 && str[i] && str[i + 1])
			i = ft_strlen_quote_loop_increment(str, i, 39, &len);
		else if (str[i])
			i++;
	}
	return (len);
}

size_t	ft_strlen_quote(const char *str, int builtin_detected)
{
	size_t len;

	len = ft_strlen(str);
	return (ft_strlen_quote_loop(str, len, builtin_detected));
}
