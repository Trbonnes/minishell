/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/15 16:20:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		g_last_return_value = 0;
t_env	*g_env_list = (t_env *) { 0 };
pid_t	g_pid = 1;

int		ft_print_syntax_error(char *str, int i)
{
	g_last_return_value = 2;
	write(2, "syntax error near unexpected token ", 35);
	write(2, &str[i], 1);
	write(2, "\n", 1);
	free(str);
	return (1);
}

int		ft_syntax_error_comma(char *str)
{
	int		i;
	bool	detected;

	i = 0;
	while (str[i])
	{
		detected = false;
		while (str[i] && str[i] != ';' && str[i] != '|')
		{
			if (str[i] == '\\' && (str[i + 1] == ';' || str[i + 1] == '|'))
				i += 2;
			if (str[i] != ' ' && str[i] != '	')
				detected = true;
			if (str[i])
				i++;
		}
		if (str[i] && detected == false)
			return (ft_print_syntax_error(str, i));
		else if (str[i])
			i++;
	}
	return (0);
}

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
