/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:33:29 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:33:29 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int			quote_executable_simple(char **str, int i)
{
	if (str[0][i + 1] == 39 && (str[0][i + 2] == ' ' || str[0][i + 2] == '\0')
	&& (i == 0 || str[0][i - 1] == ' '))
	{
		str[0][i] = 26;
		str[0][i + 1] = 26;
	}
	else
	{
		i++;
		while (str[0][i] && str[0][i] != 39)
			i++;
	}
	return (i);
}

int			quote_executable_double(char **str, int i)
{
	if (str[0][i + 1] == 34 && (str[0][i + 2] == ' ' || str[0][i + 2] == '\0')
	&& (i == 0 || str[0][i - 1] == ' '))
	{
		str[0][i] = 26;
		str[0][i + 1] = 26;
	}
	else
	{
		str[0][i++] = 39;
		while (str[0][i] && str[0][i] != 34)
			i++;
		str[0][i] = 39;
	}
	return (i);
}

void		ft_quote_executable(char **str)
{
	int i;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == 39)
			i = quote_executable_simple(str, i);
		else if (str[0][i] == 34)
			i = quote_executable_double(str, i);
		else if (str[0][i] == ' ')
			str[0][i] = 39;
		if (str[0][i])
			i++;
	}
}
