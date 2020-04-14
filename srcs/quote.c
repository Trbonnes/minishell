/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:08:45 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/14 15:47:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern pid_t	g_pid;

int			ft_detect_quote(char *prompt, char c)
{
	int i;

	i = -1;
	while (prompt[++i])
		if (prompt[i] == c)
		{
			prompt[i + 1] = '\0';
			return (1);
		}
	return (0);
}

void		ft_wait_quote(char c, char **quote_str)
{
	(void)c;
	(void)quote_str;
}

int			ft_redirection_quote(int i, char **str, char **quote_str, char c)
{
	i++;
	while (str[0][i] && str[0][i] != c)
		i++;
	if (str[0][i] == '\0')
		ft_wait_quote(c, quote_str);
	else
		i++;
	return (i);
}
