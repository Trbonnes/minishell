/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 06:46:23 by trdella-          #+#    #+#             */
/*   Updated: 2020/05/15 16:08:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env	*g_env_list;
extern pid_t	g_pid;

int			ft_free_params(char **params, int ret)
{
	int i;

	i = 0;
	while (params[i])
		free(params[i++]);
	free(params);
	return (ret);
}

int			ft_selfmade_binary(t_parsing *parser, char **env, char **params)
{
	if (execve(parser->executable, params, env) == -1)
	{
		g_last_return_value = 1;
		return (-1);
	}
	g_last_return_value = 0;
	return (1);
}

int			ft_str_check(char *str)
{
	int i;

	i = 0;
	if (str[0] == 3)
	{
		write(1, " exit\n", 6);
		free(str);
		return (-1);
	}
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int			ft_str_loop(char **env, int i, char *str)
{
	t_parsing	*parser;
	t_parsing	*parser_save;

	while (str[i])
	{
		if (!(str = parser_init(str, i, &parser, &parser_save)))
			return (1);
		if (str[i] == '|')
			i++;
		i = ft_increment_begin(str, i);
		parser->builtin_detected = ft_select_builtin(&parser->param);
		if (parser->builtin_detected == 7)
			parser->executable = strdup(parser->param);
		free(parser->param);
		i = ft_increment_option(str, i, parser);
		if (ft_parser_get(parser, str, i) == -1)
			return (-1);
		i = ft_increment_end(str, i);
		if (str[i] != '|' || str[i - 1] == '\\')
			if (ft_execute_and_clear(parser, parser_save, env) == -1)
			{
				free(str);
				return (-1);
			}
	}
	free(str);
	return (i);
}

int			ft_detect_builtin(char **env)
{
	int			i;
	char		*str;

	i = 0;
	write(1, "minishell$>", 11);
	get_next_line(0, &str);
	if (ft_str_check(str) == -1)
		return (0);
	if (ft_syntax_error_comma(str) == 1)
		return (1);
	if (str[i] != '|')
	{
		if (ft_str_loop(env, i, str) == -1)
			return (-1);
	}
	else
	{
		g_last_return_value = 2;
		write(2, "syntax error near unexpected token |\n", 37);
	}
	return (1);
}
