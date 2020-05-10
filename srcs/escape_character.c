/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 12:08:01 by user42            #+#    #+#             */
/*   Updated: 2020/05/10 14:20:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_escapelen(char **str)
{
	int i;
	int len;
	int	quote;

	i = 0;
	quote = 0;
	len = ft_strlen(str[0]);
	while (str[0][i])
	{
		quote = ft_quote_check(str[0][i], quote);
		if (str[0][i] == '\\' && quote != '\'')
		{
			if (quote == 0 && ((str[0][i + 1] != '\0' || str[0][i + 1] != ' ' || str[0][i + 1] != '	')))
				len++;
			else if (quote == '"' && str[0][i + 1] == '\\')
			{
				len -= 1;
				i++;
			}
			i++;
		}
		else if (str[0][i])
			i++;
	}
	return (len);
}

void	ft_escape_character_dup(char **str, char *tmp)
{
	int i;
	int j;
	int quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[0][i])
	{
		quote = ft_quote_check(str[0][i], quote);
		if (str[0][i] == '\\' && quote != '\'')
		{
			if (quote == 0)
			{
				if (str[0][i + 1] == '\0' || str[0][i + 1] == ' ' || str[0][i + 1] == '	')
					tmp[j++] = str[0][i];
				else
				{
					tmp[j++] = '\'';
					tmp[j++] = str[0][++i];
					tmp[j++] = '\'';
				}
			}
			else if (quote == '"' && str[0][i + 1] == '\\')
				tmp[j++] = str[0][++i];
			else if (quote == '"')
			{
				tmp[j++] = str[0][i++];
				tmp[j++] = str[0][i];
			}
			if (str[0][i])
				i++;
		}
		else if (str[0][i])
			tmp[j++] = str[0][i++];
	}
	tmp[j] = '\0';
}

void	ft_handle_escape_character(char **str)
{
	int		len;
	char	*tmp;

	len = ft_escapelen(str);
	if (!(tmp = malloc (sizeof(char) * len + 1)))
		return ;
	ft_escape_character_dup(str, tmp);
	free(str[0]);
	str[0] = ft_strdup(tmp);
	free(tmp);
}