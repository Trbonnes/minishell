/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:41:06 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/23 10:41:40 by trbonnes         ###   ########.fr       */
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
