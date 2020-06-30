/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:31:30 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:31:31 by trbonnes         ###   ########.fr       */
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
		write(1, "Quit (core dumped)\n", 19);
	else
		ft_putstr("\b\b  \b\b");
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
	return (g_last_return_value);
}
