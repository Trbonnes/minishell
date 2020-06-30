/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:33:40 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:33:41 by trbonnes         ###   ########.fr       */
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

int		ft_quote_check(char *str, int i, int quote)
{
	if (str[i] == 34 && (i == 0 || str[i - 1] != '\\'))
	{
		if (quote == 0)
			quote = 34;
		else if (quote == 34)
			quote = 0;
	}
	if (str[i] == 39 && (i == 0 || str[i - 1] != '\\'))
	{
		if (quote == 0)
			quote = 39;
		else if (quote == 39)
			quote = 0;
	}
	return (quote);
}

int		ft_quote_before_after(const char *str, int i,
int builtin_detected)
{
	if (builtin_detected == 6
	&& str[i] && str[i] == 34 && str[i + 1] == 34
	&& (i == 0 || str[i - 1] != '\\'))
		i += 2;
	if (builtin_detected == 6
	&& str[i] && str[i] == 39 && str[i + 1] == 39
	&& (i == 0 || str[i - 1] != '\\'))
		i += 2;
	return (i);
}
