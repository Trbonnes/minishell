/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/23 16:51:32 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

t_env *g_env_list = (t_env *) { 0 };
static pid_t g_pid;

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_pid == 0)
		exit(0);
	else
		write(1, "\n", 1);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		write(1, "Quit: 3\n", 8);
		exit(0);
	}
}

int		main(int ac, char **av, char **env)
{
	(void)(ac + av);
	signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, sigquit_handler);
	ft_environment_parsing(env);
	while (ft_detect_builtin() > 0)
	{
		system("leaks minishell");
		printf("Command Executed\n");
	}
	ft_envclear(&g_env_list);
	return (0);
}
