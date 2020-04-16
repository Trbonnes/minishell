/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trombone <trombone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:55:57 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/16 14:10:00 by trombone         ###   ########.fr       */
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
	int i;
	int	j;

	i = 0;
	j = 0;
	while (parsed[i])
	{
		if (parsed[i] == '$' && (i == 0 || parsed[i - 1] != '\''))
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
