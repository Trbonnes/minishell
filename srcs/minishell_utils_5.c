/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:57 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/18 16:26:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_find_dollar(char *parsed)
{
	int i;

	i = 0;
	while (parsed[i] != '$')
		i++;
	return (i);
}

char	*ft_replace_env_loop(t_env *search, char *parsed,
char *parsed_cpy, int k)
{
	int		i;
	int		j;
	bool	into_q;

	i = 0;
	j = 0;
	into_q = false;
	while (parsed[i])
	{
		if (parsed[i] == '\'' && into_q)
			into_q = false;
		else if (parsed[i] == '\'' && !into_q)
			into_q = true;
		if (parsed[i] == '$' && !into_q)
		{
			while (search->ref[k])
				parsed_cpy[j++] = search->ref[k++];
			i++;
			while (parsed[i] != ' ' && parsed[i] != '\"' &&
			parsed[i] != '\'' && parsed[i] != '$' && parsed[i])
				i++;
			while (parsed[i])
				parsed_cpy[j++] = parsed[i++];
			break ;
		}
		if (parsed[i])
			parsed_cpy[j++] = parsed[i++];
	}
	parsed_cpy[j] = '\0';
	return (parsed_cpy);
}
