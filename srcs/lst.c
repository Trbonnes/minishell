/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 08:44:17 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/18 08:18:55 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
static int		g_status;

char	*ft_no_space(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (str[j + i] != ' ' && str[j + i])
		j++;
	if (!(copy = ft_substr(str, i, j)))
		return (NULL);
	free(str);
	return (copy);
}

void	ft_pid_back(t_pid **lst, t_pid *new)
{
	t_pid *save;

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

t_pid	*ft_newelem(pid_t pid)
{
	t_pid	*elem;

	if (!(elem = malloc(sizeof(t_pid))))
		return (NULL);
	elem->pid = pid;
	elem->next = 0;
	return (elem);
}

void	ft_lstclear(t_pid **jul)
{
	t_pid	*tmp;
	t_pid	*supp;

	tmp = *jul;
	if (jul == NULL)
		return ;
	tmp = *jul;
	while (tmp)
	{
		supp = tmp;
		tmp = tmp->next;
		free(supp);
	}
}

void	ft_wait_children(t_pid *jul)
{
	t_pid	*save;

	save = jul;
	while (jul)
	{
		waitpid(jul->pid, &g_status, 0);
		while (!WIFEXITED(g_status) && !WIFSIGNALED(g_status))
			waitpid(jul->pid, &g_status, 0);
		jul = jul->next;
	}
	g_last_return_value = g_status;
	jul = save;
	ft_lstclear(&jul);
}
