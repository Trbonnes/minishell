/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:39:41 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/18 12:56:35 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env	*g_env_list;
extern pid_t	g_pid;

char	*ft_last_value(char *parsed)
{
	char	*parsed_cpy;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = ft_itoa(g_last_return_value);
	while (tmp[j])
		j++;
	if (!(parsed_cpy = malloc(sizeof(char) * (j + ft_strlen(parsed) + 1))))
		return (NULL);
	j = 0;
	while (parsed[i] != '$')
		parsed_cpy[j++] = parsed[i++];
	while (tmp[k])
		parsed_cpy[j++] = tmp[k++];
	while (parsed[i] != ' ' && parsed[i])
		i++;
	while (parsed[i])
		parsed_cpy[j++] = parsed[i++];
	parsed_cpy[j] = '\0';
	return (parsed_cpy);
}

char	*ft_replace_env(t_env *search, char *parsed)
{
	char	*parsed_cpy;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (search->ref[k - 1] != '=')
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
	return (parsed_cpy);
}

char	*ft_delete_dollar(char *parsed)
{
	char	*parsed_cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (parsed[i] != '$')
		i++;
	if (parsed[i + 1] == '?')
		return (ft_last_value(parsed));
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
	return (parsed_cpy);
}

char	*ft_dollar_call(char *parsed, char *env_check)
{
	char	*parsed_cpy;
	t_env	*search;
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (parsed[++j])
		if (parsed[j] == '$')
		{
			j++;
			while (parsed[j] != ' ' && parsed[j])
				env_check[i++] = parsed[j++];
			env_check[i] = '\0';
			break ;
		}
	search = g_env_list;
	while (search && ft_strcmp(env_check, search->key) != 0)
		search = search->next;
	if (search != NULL)
		parsed_cpy = ft_replace_env(search, parsed);
	else
		parsed_cpy = ft_delete_dollar(parsed);
	return (parsed_cpy);
}

char	*ft_dollar_env(char *parsed)
{
	char	*env_check;
	char	*parsed_cpy;
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (parsed[++j])
		if (parsed[j] == '$')
		{
			while (parsed[j] != ' ' && parsed[j++])
				i++;
			break ;
		}
	if (i == 0)
		return (parsed);
	if (!(env_check = malloc(sizeof(char) * i + 1)))
		return (NULL);
	parsed_cpy = ft_dollar_call(parsed, env_check);
	free(parsed);
	free(env_check);
	return (parsed_cpy);
}