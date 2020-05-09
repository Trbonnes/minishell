/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:48:45 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/09 13:08:15 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

void	ft_parserclear(t_parsing **lst)
{
	t_parsing *tmp;
	t_parsing *supp;

	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp != 0)
	{
		free(tmp->param);
		free(tmp->redirection);
		free(tmp->executable);
		supp = tmp;
		tmp = tmp->next;
		free(supp);
	}
	lst = NULL;
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

t_env	*ft_new_env(char *env)
{
	t_env	*new;
	int		i;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->key = ft_substr(env, 0, i);
	new->ref = ft_strdup(env);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env *save;

	save = *lst;
	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (save->next)
			save = save->next;
		save->next = new;
	}
}
