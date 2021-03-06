/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:36:14 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:33:34 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_redirection_calculate(int i, char **str, char **quote_str)
{
	while (str[0][i] && (str[0][i] == '<'
	|| str[0][i] == '>' || str[0][i] == ' '))
		i++;
	if (str[0][i] == 34)
		i = ft_redirection_quote(i, str, quote_str, 34);
	else if (str[0][i] == 39)
		i = ft_redirection_quote(i, str, quote_str, 39);
	else
		while (str[0][i] && str[0][i] != '<'
		&& str[0][i] != '>' && str[0][i] != ' ')
			i++;
	return (i);
}

int		ft_redirection_setup(char *str, char **actual)
{
	int		i;
	int		j;
	char	*redirection;
	char	*tmp;
	char	*quote_str;

	i = 0;
	j = -1;
	tmp = NULL;
	quote_str = NULL;
	if (actual[0])
		tmp = ft_strdup(actual[0]);
	free(actual[0]);
	i = ft_redirection_calculate(i, &str, &quote_str);
	if (!(redirection = malloc(sizeof(char) * i + 1)))
		return (-1);
	while (++j < i && str[j])
		redirection[j] = str[j];
	ft_quote_cpy(i, j, &redirection, &quote_str);
	actual[0] = ft_strjoin(tmp, redirection);
	free(tmp);
	free(redirection);
	free(quote_str);
	return (j);
}

char	*ft_redirection_check(char **redirection_str)
{
	if (!redirection_str[0])
	{
		if (!(redirection_str[0] = malloc(sizeof(char) * 1)))
			return (NULL);
		redirection_str[0][0] = '\0';
	}
	return ("OK");
}

char	*ft_parser_redirection(char **builtin_str, int builtin_detected)
{
	int		i;
	int		q;
	char	*redirection_str;

	i = -1;
	redirection_str = NULL;
	q = 0;
	while (builtin_str[0][++i])
	{
		q = ft_quote_check(builtin_str[0], i, q);
		if ((builtin_str[0][i] == '<' || builtin_str[0][i] == '>')
		&& q == 0 && (i == 0 || builtin_str[0][i - 1] != '\\'))
		{
			builtin_str[0] = ft_realloc_param_str(i, ft_redirection_setup(
			builtin_str[0] + i, &redirection_str), builtin_str[0]);
			i = -1;
		}
	}
	ft_redirection_check(&redirection_str);
	ft_handle_escape_character(builtin_str);
	if (builtin_detected == 7 || builtin_detected == 0)
		ft_quote_executable(builtin_str);
	else if (builtin_detected != 4 && builtin_detected != 2)
		ft_unquote(builtin_str, builtin_detected);
	return (redirection_str);
}
