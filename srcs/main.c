/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 15:50:29 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

t_env *g_env_list = (t_env *) { 0 };

void	ft_env_key(int i, char **env)
{
	int j;

	j = 0;
	while (env[i][j] != '=')
		j++;
	g_env_list->key = malloc(sizeof(char) * j + 1);
	j = 0;
	while (env[i][j] != '=')
	{
		g_env_list->key[j] = env[i][j];
		j++;
	}
	g_env_list->key[j] = '\0';
}

void	ft_env_ref(int i, char **env)
{
	int j;

	j = 0;
	while (env[i][j])
		j++;
	g_env_list->ref = malloc(sizeof(char) * j + 1);
	j = 0;
	while (env[i][j])
	{
		g_env_list->ref[j] = env[i][j];
		j++;
	}
	g_env_list->ref[j] = '\0';
}

void	ft_environment_parsing(char **env)
{
	int i;
	int j;
	t_env *save;

	i = 0;
	j = 0;
	g_env_list = malloc(sizeof(t_env));
	save = g_env_list;
	while (env[i])
	{
		ft_env_key(i, env);
		ft_env_ref(i, env);
		if (env[i + 1])
		{
			g_env_list->next = malloc(sizeof(t_env));
			g_env_list = g_env_list->next;
		}
		else
			g_env_list->next = NULL;
		i++;
	}

	g_env_list = save;
}

int		main(int ac, char **av, char **env)
{
	(void)(ac + av);
	ft_environment_parsing(env);
	while(ft_detect_builtin() > 0)
	{
		system("leaks minishell");
		printf("Command Executed\n");
	}
	ft_envclear(&g_env_list);
	return (0);
}
