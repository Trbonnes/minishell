/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/21 18:28:25 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

t_env *global = (t_env *) { 0 };

void	ft_environment_parsing(char **env)
{
	int i;
	int j;
	t_env *save;

	i = 0;
	j = 0;
	global = malloc(sizeof(t_env));
	save = global;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		global->key = malloc(sizeof(char) * j + 1);
		j = 0;
		while (env[i][j] != '=')
		{
			global->key[j] = env[i][j];
			j++;
		}
		global->key[j] = '\0';
		j = 0;
		while (env[i][j])
			j++;
		global->ref = malloc(sizeof(char) * j + 1);
		j = 0;
		while (env[i][j])
		{
			global->ref[j] = env[i][j];
			j++;
		}
		global->ref[j] = '\0';
		global->next = malloc(sizeof(t_env));
		global = global->next;
		i++;
	}
	global = save;
}

int		main(int ac, char **av, char **env)
{
	(void)(ac + av);
	ft_environment_parsing(env);
	while(ft_detect_builtin() > 0)
		printf("Command Executed\n");
	return (0);
}