/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:28:16 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:28:16 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_spaces_substitute(char *tmp, int z)
{
	int		i;

	if (z == 0)
	{
		i = -1;
		while (tmp[++i])
			if (tmp[i] == 26 && tmp[i + 1] == ' ')
				tmp[i + 1] = 27;
	}
	if (z == 1)
	{
		i = -1;
		while (tmp[++i])
			if (tmp[i] == 27)
				tmp[i] = ' ';
	}
}

void	ft_setup_escape_quotes_back(char *tmp, int i)
{
	int j;

	j = i;
	while (j > 0 && tmp[j] != ' ')
	{
		tmp[j] = tmp[j - 1];
		tmp[j - 1] = 127;
		j--;
	}
	if (j == 0 && tmp[j] != '\'' && tmp[j + 1] != '\'')
		tmp[j] = '\'';
	else if (tmp[j] != '\'' && tmp[j + 1] != '\'')
		tmp[j + 1] = '\'';
}

void	ft_setup_escape_quotes_front(char *tmp, int i)
{
	int	j;

	j = i;
	while (tmp[j] && tmp[j] != ' ')
	{
		if (tmp[j + 1] != '\0')
		{
			tmp[j] = tmp[j + 1];
			tmp[j + 1] = 127;
		}
		else
		{
			if (tmp[j] != ' ')
				j++;
			break ;
		}
		j++;
	}
	if (tmp[j] == 26)
		tmp[j] = '\'';
	if (tmp[j] != '\'' && tmp[j - 1] != '\'')
		tmp[j - 1] = '\'';
}

int		ft_setup_escape_quotes(char *tmp, int i)
{
	if (tmp[i + 1] == '\'')
		tmp[i + 1] = 31;
	ft_setup_escape_quotes_back(tmp, i);
	i += 2;
	ft_setup_escape_quotes_front(tmp, i);
	return (i);
}

void	ft_escape_spaces(char *tmp)
{
	int		i;

	ft_spaces_substitute(tmp, 0);
	i = 0;
	while (tmp[i])
	{
		while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '	'))
			i++;
		if (tmp[i] == 26 && tmp[i + 1] != ' ' && tmp[i + 1] != '	')
			i = ft_setup_escape_quotes(tmp, i);
		else if (tmp[i])
			i++;
	}
	ft_spaces_substitute(tmp, 1);
}
