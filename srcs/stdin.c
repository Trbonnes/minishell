/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/13 08:30:06 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;
extern pid_t	g_pid;

const static char *const	g_builtins[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"export",
	"pwd",
	"unset",
	NULL
};

int			ft_select_builtin(char *builtin_str)
{
	int	i;

	i = -1;
	while (builtin_str[++i])
		builtin_str[i] = ft_tolower(builtin_str[i]);
	i = -1;
	while (g_builtins[++i] != NULL
	&& ft_strcmp(builtin_str, g_builtins[i]) != 0)
		;
	return (i);
}

char		*ft_parser_cmd(char *str)
{
	char	*parsed;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != ';'
	&& str[i] != '|' && str[i] != '<' && str[i] != '>' && ++i)
		j++;
	if (!(parsed = malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';'
	&& str[i] != '|' && str[i] != '<' && str[i] != '>')
		parsed[j++] = str[i++];
	parsed[j] = '\0';
	return (parsed);
}

int			ft_option(char *str, t_parsing *parser, int i)
{
	if (parser->builtin_detected != 1 && parser->builtin_detected != 7)
	{
		write(2, "minishell: ", 11);
		write(2, &str[i], 1);
		write(2, &str[++i], 1);
		write(2, ": invalid option\n", 17);
		parser->builtin_detected = 8;
	}
	if (parser->builtin_detected == 8)
		return (i);
	else if (str[i + 1] == 'n' && str[i + 2] == ' ')
	{
		parser->echo_option = 1;
		i += 3;
	}
	return (i);
}

int			parser_init(char *str, int i, t_parsing **parser,
t_parsing **parser_save)
{
	if (str[i] != '|')
	{
		if (!(parser[0] = malloc(sizeof(t_parsing))))
			return (-1);
		parser[0]->echo_option = 0;
		parser[0]->next = NULL;
		parser[0]->executable = NULL;
		parser[0]->index = 0;
		parser_save[0] = parser[0];
	}
	else
	{
		if (!(parser[0]->next = malloc(sizeof(t_parsing))))
			return (-1);
		parser[0] = parser[0]->next;
		parser[0]->echo_option = 0;
		parser[0]->next = NULL;
		parser[0]->executable = NULL;
		parser[0]->index = 0;
		i++;
	}
	if ((parser[0]->param = ft_parser_cmd(str + i)) == NULL)
		return (-1);
	return (1);
}

int			ft_execute_and_clear(t_parsing *parser,
t_parsing *parser_save, char **env)
{
	int r;

	r = 0;
	if (parser->builtin_detected != 8)
		r = ft_execute_builtin(parser_save, env);
	ft_parserclear(&parser_save);
	parser_save = NULL;
	parser = NULL;
	return (r);
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
		parser_init(str, i, &parser, &parser_save);
		if (str[i] == '|')
			i++;
		i = ft_increment_begin(str, i);
		parser->builtin_detected = ft_select_builtin(parser->param);
		if (parser->builtin_detected == 7)
			parser->executable = strdup(parser->param);
		free(parser->param);
		i = ft_increment_option(str, i, parser);
		if (ft_parser_get(parser, str, i) == -1)
			return (-1);
		i = ft_increment_end(str, i);
		if (str[i] != '|')
			if (ft_execute_and_clear(parser, parser_save, env) == -1)
			{
				free(str);
				return (-1);
			}
	}
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
	if (str[i] != '|')
	{
		if ((i = ft_str_loop(env, i, str)) == -1)
			return (-1);
	}
	else
		write(2, "syntax error near unexpected token |\n", 37);
	free(str);
	return (1);
}
