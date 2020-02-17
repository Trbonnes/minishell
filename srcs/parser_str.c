/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:39:30 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/17 10:21:59 by trbonnes         ###   ########.fr       */
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

char	*ft_dollar_env(char *parsed)
{
	char	*env_check;
	char	*parsed_cpy;
	t_env	*search;
	int		i;
	int		j;
	int		k;
	
	j = -1;
	i = 0;
	while (parsed[++j])
		if (parsed[j] == '$')
		{
			while (parsed[j] != ' ' && parsed[j])
			{
				j++;
				i++;
			}
			break;
		}
	if (i == 0)
		return(parsed);
	if (!(env_check = malloc(sizeof(char) * i + 1)))
		return (NULL);
	j = -1;
	i = 0;
	while (parsed[++j])
		if (parsed[j] == '$')
		{
			j++;
			while (parsed[j] != ' ' && parsed[j])
				env_check[i++] = parsed[j++];
			env_check[i] = '\0';
			break;
		}
	search = g_env_list;
	while (search && ft_strcmp(env_check, search->key) != 0)
		search = search->next;
	if (search != NULL)
	{
		i = 0;
		j = 0;
		k = 0;
		while (search->ref[k] != '=')
			k++;
		k++;
		while (search->ref[k + j])
			j++;
		if (!(parsed_cpy = malloc(sizeof(char) * (j + ft_strlen(parsed) + 1))))
			return (NULL);
		j = 0;
		while (parsed[i] != '$')
			parsed_cpy[j++] = parsed[i++];
		while (search->ref[k])
			parsed_cpy[j++] = search->ref[k++];
		while (parsed[i] != ' ' && parsed[i])
			i++;
		while (parsed[i])
			parsed_cpy[j++] = parsed[i++];
		parsed_cpy[j] = '\0';
	}
	else
	{
		i = 0;
		j = 0;
		while (parsed[i] != '$')
			i++;
		while (parsed[i + j] != ' ' && parsed[i + j])
			j++;
		if (!(parsed_cpy = malloc(sizeof(char) * (ft_strlen(parsed) - j + 1))))
			return (NULL);
		i = 0;
		j = 0;
		while (parsed[i] != '$')
			parsed_cpy[j++] = parsed[i++];
		while (parsed[i] && parsed[i] != ' ')
			i++;
		while (parsed[i])
			parsed_cpy[j++] = parsed[i++];
		parsed_cpy[j] = '\0';
	}
	free(parsed);
	free(env_check);
	return (parsed_cpy);
}

char	*ft_parser_param(char *str)
{
	char	*parsed;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != ';' && str[i] != '|' && ++i)
		j++;
	if (!(parsed = malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ';' && str[i] != '|')
		parsed[j++] = str[i++];
	parsed[j] = '\0';
	return (ft_dollar_env(parsed));
}
