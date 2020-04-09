/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_incrementers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trombone <trombone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:34:56 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/09 18:49:29 by trombone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_increment_begin(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != ';'
	&& str[i] != '|' && str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

int		ft_increment_end(char *str, int i)
{
	while (str[i] != '\0' && str[i] != ';' && str[i] != '|')
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_parser_param_quote(str + i, str[i]);
		i++;
	}
	if (str[i] == '|')
		return (i);
	if (str[i] != '\0')
		i++;
	return (i);
}

int		ft_parser_get(t_parsing *parser, char *str, int i)
{
	if ((parser->param = ft_parser_param(str + i)) == NULL)
		return (-1);
	if ((parser->redirection = ft_parser_redirection(&parser->param)) == NULL)
		return (-1);
	return (1);
}

int		ft_increment_option(char *str, int i, t_parsing *parser)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i] && parser->builtin_detected < 7)
		i = ft_option(str, parser, i);
	return (i);
}
