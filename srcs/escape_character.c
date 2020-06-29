/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 12:08:01 by user42            #+#    #+#             */
/*   Updated: 2020/06/29 14:35:48 by user42           ###   ########.fr       */
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
		quote = ft_quote_check(str[0], i, quote);
		if (str[0][i] == '\\' && quote != '\'')
		{
			if (quote == 0 && str[0][i + 1] != '\0')
				len++;
			else if (quote == '"' && str[0][i + 1] == '\\' && ++i)
				len -= 1;
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
		quote = ft_quote_check(str[0], i, quote);
		if (str[0][i] == '\\' && quote != '\'' && str[0][i + 1])
		{
			if (quote == 0)
				ft_escape_zero(str, tmp, &i, &j);
			else if (quote == '"' && str[0][i + 1] == '\\')
				tmp[j++] = str[0][++i];
			else if (quote == '"')
				ft_escape_quote(str, tmp, &i, &j);
			if (str[0][i])
				i++;
		}
		else if (str[0][i])
			tmp[j++] = str[0][i++];
	}
	tmp[j] = '\0';
}

size_t	ft_strdup_escape_len(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		if (str[i] != 127)
			i++;
	return (i);
}

char	*ft_strdup_escape(char *str)
{
	char	*copy;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (!(copy = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[i])
	{
		if (str[i] != 127)
			copy[j++] = str[i];
		i++;
	}
	copy[j] = '\0';
	return (copy);
}

void	ft_handle_escape_character(char **str)
{
	int		len;
	char	*tmp;

	len = ft_escapelen(str);
	if (!(tmp = malloc(sizeof(char) * len + 1)))
		return ;
	ft_escape_character_dup(str, tmp);
	ft_escape_spaces(tmp);
	free(str[0]);
	str[0] = ft_strdup_escape(tmp);
	free(tmp);
}
