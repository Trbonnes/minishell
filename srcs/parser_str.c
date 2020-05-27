/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:39:30 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/27 10:08:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;
extern pid_t	g_pid;

char	*ft_realloc_param_str(int i, int j, char *param_str)
{
	int		k;
	char	*cpy;

	if ((size_t)(i + j) > ft_strlen(param_str))
		k = i;
	else
		k = ft_strlen(param_str) - j;
	if (!(cpy = malloc(sizeof(char) * k + 1)))
		return (NULL);
	ft_bzero(cpy, k + 1);
	k = -1;
	while (++k < i)
		cpy[k] = param_str[k];
	i += j;
	while (param_str[i])
		cpy[k++] = param_str[i++];
	free(param_str);
	return (cpy);
}

int		ft_parser_full_quote(char c, char *str, char *parsed)
{
	int i;

	i = 1;
	while (str[i] && str[i] != c)
	{
		parsed[i] = str[i];
		i++;
	}
	parsed[i] = str[i];
	if (str[i] == '\"' || str[i] == '\'')
		i++;
	return (i);
}

int		ft_parser_alloc_calculate(char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ';' && str[i] != '|')
	{
		if (ft_skip_escape(str, &i, &j) == 0
		&& (str[i] == '\"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
		{
			k = ft_parser_param_quote(str + i, str[i]);
			i += k;
			j += k;
		}
		else if (str[i] && ft_clear_spaces(str, i))
		{
			i++;
			j++;
		}
		else if (str[i])
			i++;
	}
	return (j);
}

void	ft_parser_param_loop(char *str, char *parsed, int i, int j)
{
	int k;

	k = 0;
	while (str[i] && str[i] != ';' && str[i] != '|')
	{
		if (str[i] == '\\' && (str[i + 1] == ';' || str[i + 1] == '|'))
		{
			parsed[j++] = str[i++];
			parsed[j++] = str[i++];
		}
		else if ((str[i] == '\"' || str[i] == '\'')
		&& (i == 0 || str[i - 1] != '\\'))
		{
			parsed[j] = str[i];
			k = ft_parser_full_quote(str[i], str + i, parsed + j);
			j += k;
			i += k;
		}
		else if (str[i] && ft_clear_spaces(str, i))
			parsed[j++] = str[i++];
		else if (str[i])
			i++;
	}
	parsed[j] = '\0';
}

char	*ft_parser_param(char *str)
{
	char	*parsed;
	int		i;
	int		j;

	if (!(parsed = malloc(sizeof(char) * ft_parser_alloc_calculate(str) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	ft_parser_param_loop(str, parsed, i, j);
	return (ft_dollar_env(parsed));
}
