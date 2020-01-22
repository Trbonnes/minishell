/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:08:45 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 12:30:43 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_unquote(char **str)
{
	char *tmp;

	printf("hum\n");
	tmp = ft_strdup_chr(str[0], 34);
	free(str[0]);
	printf("humhum\n");
	str[0] = ft_strdup_chr(tmp, 39);
	free(tmp);
}

int		ft_wait_quote(char **str, char c)
{
	char	*quote;
	char	*join;
	int		stop;
	int		i;

	stop = 0;
	while (stop != 1)
	{
		i = -1;
		write(1, ">", 1);
		get_next_line(0, &quote);
		while (quote[++i])
			if (quote[i] == c)
				stop = 1;
		join = ft_strjoin(str[0], quote);
		printf("free1\n");
		free(quote);
		printf("free2\n");
		free(str[0]);
		str[0] = ft_strdup(join);
		printf("free3\n");
		free(join);
	}
	i = 0;
	join = ft_strdup_chr(str[0], c);
	printf("free4\n");
	free(str[0]);
	str[0] = ft_strdup(join);
	printf("free5\n");
	free(join);
	return (ft_strlen(str[0]));
}

int		ft_redirection_calculate(int i, char **str)
{
	while (str[0][i] && (str[0][i] == '<' || str[0][i] == '>' || str[0][i] == ' '))
		i++;
	if (str[0][i] == 34)
	{
		i++;
		printf("double quote\n");
		while (str[0][i] && str[0][i] != 34)
			i++;
		if (str[0][i] == '\0')
			i = ft_wait_quote(str, 34);
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
			i = ft_wait_quote(str, 39);
		else
			i++;
		
	}
	else
		while (str[0][i] && str[0][i] != '<' && str[0][i] != '>' && str[0][i] != ' ')
			i++;
	return (i);
}
