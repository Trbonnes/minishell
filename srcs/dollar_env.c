/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 10:39:41 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/18 16:36:03 by user42           ###   ########.fr       */
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
	if (!(parsed_cpy = malloc(sizeof(char) * (ft_strlen(tmp)
	+ ft_strlen(parsed) + 1))))
		return (NULL);
	while (parsed[i] != '$')
		parsed_cpy[j++] = parsed[i++];
	while (tmp[k])
		parsed_cpy[j++] = tmp[k++];
	while (parsed[i] != ' ' && parsed[i])
		i++;
	while (parsed[i])
		parsed_cpy[j++] = parsed[i++];
	parsed_cpy[j] = '\0';
	free(tmp);
	return (parsed_cpy);
}

char	*ft_replace_env(t_env *search, char *parsed)
{
	char	*parsed_cpy;
	int		k;

	k = 1;
	while (search->ref[k] && search->ref[k - 1] != '=')
		k++;
	if (!(parsed_cpy = malloc(sizeof(char) * (ft_ref_len(search)
	+ ft_strlen(parsed) + 1))))
		return (NULL);
	return (ft_replace_env_loop(search, parsed, parsed_cpy, k));
}

char	*ft_delete_dollar(char *parsed)
{
	char	*parsed_cpy;
	int		i;
	int		j;

	i = ft_find_dollar(parsed);
	j = 1;
	if (parsed[i + 1] == '?')
		return (ft_last_value(parsed));
	while (parsed[i + j] != '$' && parsed[i + j] != '\"' &&
	parsed[i + j] != '\'' && parsed[i + j])
		j++;
	if (!(parsed_cpy = malloc(sizeof(char) * (ft_strlen(parsed) - j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (parsed[i] != '$')
		parsed_cpy[j++] = parsed[i++];
	i++;
	while (parsed[i] && parsed[i] != '$'
	&& parsed[i] != '\"' && parsed[i] != '\'')
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
		if (parsed[j] == '$' && parsed[j + 1] != '\"' && parsed[j + 1] != '\''
		&& (j == 0 || parsed[j - 1] != '\''))
		{
			j++;
			while (parsed[j] != ' ' && parsed[j] != '\"'
			&& parsed[j] != '\'' && parsed[j] != '$' && parsed[j])
				env_check[i++] = parsed[j++];
			env_check[i] = '\0';
			break ;
		}
	search = g_env_list;
	while (search && ft_strcmp(env_check, search->key) != 0)
		search = search->next;
	if (search != NULL && env_check[0] != '\0')
		return (parsed_cpy = ft_replace_env(search, parsed));
	else
		return (parsed_cpy = ft_delete_dollar(parsed));
}

char	*ft_dollar_env(char *parsed)
{
	char	*env_check;
	char	*parsed_cpy;
	int		i;
	int		j;
	bool	into_q;

	j = -1;
	i = 0;
	into_q = false;
	while (parsed[++j])
	{
		if (parsed[j] == '\'' && into_q)
			into_q = false;
		else if (parsed[j] == '\'' && !into_q)
			into_q = true;
		if (parsed[j] == '$' && parsed[j + 1] != '\0'
		&& !into_q)
		{
			j++;
			while (parsed[j] != ' ' && parsed[j] != '$' && parsed[j++])
				i++;
			break ;
		}
	}
	if (i == 0)
		return (parsed);
	if (!(env_check = malloc(sizeof(char) * i + 1)))
		return (NULL);
	env_check[0] = '\0';
	parsed_cpy = ft_dollar_call(parsed, env_check);
	free(parsed);
	free(env_check);
	return (ft_dollar_env(parsed_cpy));
}
