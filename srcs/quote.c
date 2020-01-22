/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:08:45 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 16:05:20 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_unquote(char **str)
{
	char *tmp;

	tmp = ft_strdup_chr(str[0], 34);
	free(str[0]);
	str[0] = ft_strdup_chr(tmp, 39);
	free(tmp);
}

int		ft_detect_quote(char *prompt, char c)
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

int		ft_wait_quote(char c, char **quote_str)
{
	char	*prompt;
	char	*join;
	int		stop;
	int		i;

	stop = 0;
	while (stop != 1)
	{
		write(1, ">", 1);
		get_next_line(0, &prompt);
		stop = ft_detect_quote(prompt, c);
		join = ft_strjoin(quote_str[0], prompt);
		free(prompt);
		free(quote_str[0]);
		quote_str[0] = ft_strdup(join);
		free(join);
	}
	join = ft_strdup_chr(quote_str[0], c);
	free(quote_str[0]);
	i = ft_strlen(join);
	if (!(quote_str[0] = malloc(sizeof(char) * i + 1)))
		return (-1);
	i = -1;
	while (join[++i])
		quote_str[0][i] = join[i];
	quote_str[0][i] = '\0';
	free(join);
	return (ft_strlen(quote_str[0]));
}

int		ft_redirection_calculate(int i, char **str, char **quote_str)
{
	while (str[0][i] && (str[0][i] == '<'
	|| str[0][i] == '>' || str[0][i] == ' '))
		i++;
	if (str[0][i] == 34)
	{
		i++;
		printf("double quote\n");
		while (str[0][i] && str[0][i] != 34)
			i++;
		if (str[0][i] == '\0')
			i += ft_wait_quote(34, quote_str);
		else
			i++;
	}
	else if (str[0][i] == 39)
	{
		i++;
		printf("simple quote\n");
		while (str[0][i] && str[0][i] != 39)
			i++;
		if (str[0][i] == '\0')
			i += ft_wait_quote(39, quote_str);
		else
			i++;
	}
	else
		while (str[0][i] && str[0][i] != '<'
		&& str[0][i] != '>' && str[0][i] != ' ')
			i++;
	return (i);
}
