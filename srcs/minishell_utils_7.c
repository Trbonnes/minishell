/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:07:53 by user42            #+#    #+#             */
/*   Updated: 2020/05/09 14:30:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

int	ft_clear_spaces(char *str, int i)
{
	if (str[i] != ' ' && str[i] != '	' )
		return (1);
	if  (str[i] == ' ' && str[i + 1] && str[i + 1] != ' '
	&& str[i + 1] != '	' && str[i + 1] != ';' && str[i + 1] != '|')
		return (1);
	if (str[i] == '	' && str[i + 1] && str[i + 1] != '	'
	&& str[i + 1] != ' ' && str[i + 1] != ';' && str[i + 1] != '|')
		return (1);
	return (0);
}
