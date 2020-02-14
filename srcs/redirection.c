/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:36:14 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/14 15:35:55 by trdella-         ###   ########.fr       */
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

char	*ft_parser_redirection(char **builtin_str)
{
	int		i;
	int		j;
	int		quote;
	char	*redirection_str;

	i = -1;
	redirection_str = NULL;
	quote = 0;
	while (builtin_str[0][++i])
	{
		quote = ft_quote_check(builtin_str[0][i], quote);
		if ((builtin_str[0][i] == '<' || builtin_str[0][i] == '>')
		&& quote == 0)
		{
			j = ft_redirection_setup(builtin_str[0] + i, &redirection_str);
			builtin_str[0] = ft_realloc_param_str(i, j, builtin_str[0]);
			i = -1;
		}
	}
	if (quote != 0)
		ft_wait_quote(quote, builtin_str);
	ft_redirection_check(&redirection_str);
	ft_unquote(builtin_str);
	return (redirection_str);
}
