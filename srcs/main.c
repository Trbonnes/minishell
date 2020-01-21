/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/21 18:01:38 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

t_env global = (t_env) { 0 };

void	ft_environment_parsing(char **env)
{
	int i;
	//int j;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int		main(int ac, char **av, char **env)
{
	(void)(ac + av);
	ft_environment_parsing(env);
	while(ft_detect_builtin() > 0)
		printf("Command Executed\n");
	return (0);
}