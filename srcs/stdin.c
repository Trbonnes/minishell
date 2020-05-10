/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/10 14:07:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env	*g_env_list;
extern pid_t	g_pid;

static const char *const	g_builtins[] = {
	"cd",
	"echo",
	"env",
	"exit",
	"export",
	"pwd",
	"unset",
	NULL
};

int			ft_select_builtin(char **builtin_str)
{
	int	i;

	i = -1;
	i = -1;
	while (g_builtins[++i] != NULL
	&& ft_strcmp(builtin_str[0], g_builtins[i]) != 0)
		;
	if (i == 7 && builtin_str[0][0] == '$')
	{
		i = -1;
		builtin_str[0] = ft_dollar_env(builtin_str[0]);
		i = 8;
		if (builtin_str[0][0])
		{
			write(2, "minishell: ", 11);
			write(2, builtin_str[0], ft_strlen(builtin_str[0]));
			write(2, ": command not found\n", 20);
			g_last_return_value = 127;
		}
	}
	return (i);
}

char		*ft_parser_cmd(char *str)
{
	char	*parsed;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '	' && str[i] != ';'
	&& str[i] != '|' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\'')
			while (++j && str[++i] && str[i] != '\'')
				;
		else if (str[i] == '"')
			while (++j && str[++i] && str[i] != '"')
				;
		else if (str[i] && ++i)
			j++;
	}
	if (!(parsed = malloc(sizeof(char) * j + 1)))
		return (NULL);
	return (ft_parser_cmd_full(str, parsed, i, j));
}

int			ft_option(char *str, t_parsing *parser, int i)
{
	if (parser->builtin_detected != 1 && parser->builtin_detected != 7
	&& ft_isalpha(str[i + 1]))
	{
		write(2, "minishell: ", 11);
		write(2, &str[i], 1);
		while (str[++i] && ft_isalpha(str[i]))
			write(2, &str[i], 1);
		write(2, ": invalid option\n", 17);
		g_last_return_value = 1;
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
	if (str[i] != '|' || str[i - 1] == '\\')
	{
		if (!(parser[0] = malloc(sizeof(t_parsing))))
			return (-1);
		parser_save[0] = parser[0];
	}
	else
	{
		if (!(parser[0]->next = malloc(sizeof(t_parsing))))
			return (-1);
		parser[0] = parser[0]->next;
		i++;
	}
	parser[0]->echo_option = 0;
	parser[0]->next = NULL;
	parser[0]->executable = NULL;
	parser[0]->index = 0;
	parser[0]->builtin_detected = -1;
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
