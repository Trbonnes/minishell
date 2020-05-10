/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:07:53 by user42            #+#    #+#             */
/*   Updated: 2020/05/10 11:50:13 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_exit2(char **split)
{
	int i;

	i = 0;
	if (split[0][0] == 0)
		exit(0);
	while (split[0][i])
	{
		if (!(split[0][i] == '-' && i == 0))
		{
			if (!(split[0][i] >= '0' && split[0][i] <= '9'))
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
	return (0);
}
