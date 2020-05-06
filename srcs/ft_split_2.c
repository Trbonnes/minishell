/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:04:22 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/06 11:17:43 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;

char	*ft_strdupcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (i + j + 2))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '=';
	i++;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';

	return (str);
}

void	ft_change_pwd(void)
{
	t_env	*save;
	t_env	*old;
	char	*pwd;
	char	new[1024];

	old = g_env_list;
	save = g_env_list;
	getcwd(new, 1024);
	while ((ft_strcmp(old->key, "PWD") != 0))
		old = old->next;
	pwd = ft_substr(old->ref, 4, ft_strlen(old->ref) - 4);
	while ((ft_strcmp(g_env_list->key, "OLDPWD") != 0))
		g_env_list = g_env_list->next;
	free (g_env_list->ref);
	g_env_list->ref = ft_strdupcat("OLDPWD", pwd);
	printf("new = %s\n", new);
	free(old->ref);
	old->ref = ft_strdupcat("PWD", new);
	g_env_list = save;
	free(pwd);
}

char		**ft_no_args(void)
{
	char **tableau;

	if (!(tableau = malloc(sizeof(char*) * 2)))
		return (NULL);
	if (!(tableau[0] = malloc(sizeof(char*) * 1)))
		return (NULL);
	tableau[0][0] = '\0';
	tableau[1] = 0;
	return (tableau);
}
