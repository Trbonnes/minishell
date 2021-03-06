/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:32:49 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:32:50 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_exit2(char **split)
{
	int i;

	i = 0;
	if (!split[0])
		exit(0);
	while (split[0][i])
	{
		if (!(split[0][i] == '-' && i == 0)
		|| (split[0][i] == '-' && split[0][i + 1] == '\0'))
		{
			if (!(split[0][i] >= '0' && split[0][i] <= '9')
			|| (split[0][i + 1] == '-' && split[0][i] == '\0'))
			{
				ft_putstr("bash: exit: ");
				ft_putstr(split[0]);
				ft_putstr(" : numeric argument required\n");
				ft_free_params(split, 0);
				exit(2);
			}
		}
		i++;
	}
}

int		ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

int		ft_clear_spaces(char *str, int i)
{
	if (str[i] != ' ' && str[i] != '	')
		return (1);
	if (str[i] == ' ' && str[i + 1] && str[i + 1] != ' '
	&& str[i + 1] != '	' && str[i + 1] != ';' && str[i + 1] != '|')
		return (1);
	if (str[i] == '	' && str[i + 1] && str[i + 1] != '	'
	&& str[i + 1] != ' ' && str[i + 1] != ';' && str[i + 1] != '|')
		return (1);
	if ((str[i] == ' ' || str[i] == '	') && str[i - 1] == '\\')
		return (1);
	return (0);
}

int		ft_skip_escape(char *str, int *i, int *j)
{
	if (str[i[0]] == '\\' && (str[i[0] + 1] == ';' || str[i[0] + 1] == '|'))
	{
		i[0] += 2;
		j[0] += 2;
		return (1);
	}
	return (0);
}

int		ft_parser_param_quote(char *str, char c)
{
	int k;

	k = 1;
	while (str[k] && str[k] != c)
		k++;
	if (str[k])
		k++;
	return (k);
}
