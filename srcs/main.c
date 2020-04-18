/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/18 14:14:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		g_last_return_value = 0;
t_env	*g_env_list = (t_env *) { 0 };
pid_t	g_pid = 1;

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		ft_envclear(&g_env_list);
		exit(130);
	}
	else if (g_pid != 1)
		write(1, "\n", 1);
	else
	{
		g_last_return_value = 130;
		write(1, "\nminishell$>", 12);
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		ft_envclear(&g_env_list);
		exit(131);
	}
	else if (g_pid != 1)
		write(1, "Quit: 3\n", 8);
}

int		main(int ac, char **av, char **env)
{
	(void)(ac + av);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	ft_environment_parsing(env);
	while (ft_detect_builtin(env) > 0)
		g_pid = 1;
	ft_envclear(&g_env_list);
	return (0);
}
