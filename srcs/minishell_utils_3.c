/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:48:45 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 20:38:56 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

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
	t_env *new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->ref = ft_strdup(env);
	new->next = 0;
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

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
