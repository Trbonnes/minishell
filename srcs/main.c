/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 21:35:17 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

t_env *g_env_list = (t_env *) { 0 };

int		main(int ac, char **av, char **env)
{
	(void)(ac + av);
	ft_environment_parsing(env);
	while (ft_detect_builtin() > 0)
	{
		system("leaks minishell");
		printf("Command Executed\n");
	}
	ft_envclear(&g_env_list);
	return (0);
}
