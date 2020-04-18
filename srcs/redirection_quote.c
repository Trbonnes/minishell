/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:41:06 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/18 18:43:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_quote_cpy(int i, int j, char **redirection, char **quote_str)
{
	if (j < i)
	{
		i = 0;
		while (quote_str[0][i])
			redirection[0][j++] = quote_str[0][i++];
	}
	redirection[0][j] = '\0';
}

int		ft_quote_check(char c, int quote)
{
	if (c == 34)
	{
		if (quote == 0)
			quote = 34;
		else if (quote == 34)
			quote = 0;
	}
	if (c == 39)
	{
		if (quote == 0)
			quote = 39;
		else if (quote == 39)
			quote = 0;
	}
	return (quote);
}

int				ft_quote_before_after(const char *str, int i, int builtin_detected)
{
	if (builtin_detected == 7 && str[i] && str[i] == 34 && str[i + 1] == 34)
		i += 2;
	if (builtin_detected == 7 && str[i] && str[i] == 39 && str[i + 1] == 39)
		i += 2;
	return (i);
}
