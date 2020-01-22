/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 09:28:07 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 11:03:41 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i] || s1[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

void	ft_envdelone(t_env *lst)
{
	if (lst == NULL)
		return ;
	free(lst->key);
	free(lst->ref);
	free(lst);
	lst = NULL;
}


void	ft_envclear(t_env **lst)
{
	t_env *tmp;
	t_env *supp;

	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp != 0)
	{
		free(tmp->key);
		free(tmp->ref);
		supp = tmp;
		tmp = tmp->next;
		free(supp);
	}
	lst = NULL;
}



size_t	ft_strlen_chr(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i])
		if (str[i] != c)
			i++;
	return (i);
}

char	*ft_strdup_chr(const char *str, char c)
{
	char *copy;
	int i;
	int len;

	i = 0;
	len = ft_strlen_chr(str);
	if (!(copy = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
			copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
