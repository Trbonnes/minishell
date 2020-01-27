/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/27 15:02:40 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;
extern pid_t	g_pid;
static int		g_status;

char		*ft_path_cpy(char *env_path, int i, char *cmd)
{
	char	*path;
	int		j;

	j = 0;
	while (env_path[i + j] && env_path[i + j] != ':')
		j++;
	if (!(path = malloc(sizeof(char) * (j + ft_strlen(cmd) + 2))))
		return (NULL);
	j = 0;
	while (env_path[i] && env_path[i] != ':')
		path[j++] = env_path[i++];
	i = 0;
	path[j++] = '/';
	while (cmd[i])
		path[j++] = cmd[i++];
	path[j] = '\0';
	return (path);
}

char		*path_finding(int i, t_parsing *parser, t_env *search)
{
	char		*path;
	struct stat	buf;

	path = ft_path_cpy(search->ref, i, parser->executable);
	while (stat(path, &buf) != 0 && search->ref[i])
	{
		free(path);
		while (search->ref[i] && search->ref[i - 1] != ':')
			i++;
		path = ft_path_cpy(search->ref, i, parser->executable);
		i++;
	}
	return (path);
}

int			ft_selfmade_binary(t_parsing *parser, char **env, char **params)
{
	g_pid = fork();
	wait(&g_status);
	if (g_pid == 0)
		if (execve(parser->executable, params, env) == -1)
			return (-1);
	return (1);
}

int			ft_path_binary(t_parsing *parser, t_env *search,
char **params, char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strcmp("PATH", search->key) != 0)
		search = search->next;
	while (search->ref[i] != '=')
		i++;
	i++;
	path = path_finding(i, parser, search);
	g_pid = fork();
	wait(&g_status);
	if (g_pid == 0)
		if (execve(path, params, env) == -1)
			return (-1);
	free(path);
	i = 0;
	while (params[i])
		free(params[i++]);
	free(params);
	return (1);
}

int			ft_executable(t_parsing *parser, char **env)
{
	t_env		*search;
	char		**params;

	search = g_env_list;
	params = ft_split(parser->param, ' ');
	if (parser->executable[0] == '.' && parser->executable[1] == '/')
	{
		if (ft_selfmade_binary(parser, env, params) == -1)
			return (-1);
	}
	else if (ft_path_binary(parser, search, params, env) == -1)
		return (-1);
	return (1);
}

int			ft_execute_builtin(t_parsing *parser, char **env)
{
	printf("cmd: %d\n", parser->builtin_detected);
	printf("executable: %s\n", parser->executable);
	printf("option: %d\n", parser->echo_option);
	printf("param: %s\n", parser->param);
	printf("redirection: %s\n", parser->redirection);
	if (parser->builtin_detected == 7)
	{
		if (ft_executable(parser, env) == -1)
			write(2, "minishell: command not found\n", 29);
	}
	else
		find_fd(parser);
	return (0);
}

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
	int					i;

	i = -1;
	while (builtin_str[++i])
		builtin_str[i] = ft_tolower(builtin_str[i]);
	i = -1;
	while (g_builtins[++i] != NULL && ft_strcmp(builtin_str, g_builtins[i]) != 0)
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
		parser->builtin_detected = 7;
	}
	if (parser->builtin_detected != 7)
		return (i);
	else if (str[i + 1] == 'n')
	{
		parser->echo_option = 1;
		i += 2;
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

void		ft_execute_and_clear(t_parsing *parser,
t_parsing *parser_save, char **env)
{
	ft_execute_builtin(parser_save, env);
	ft_parserclear(&parser_save);
	parser_save = NULL;
	parser = NULL;
}

int			ft_detect_builtin(char **env)
{
	int			i;
	t_parsing	*parser;
	t_parsing	*parser_save;
	char		*str;

	i = 0;
	write(1, "minishell$>", 11);
	get_next_line(0, &str);
	while (str[i])
	{
		parser_init(str, i, &parser, &parser_save);
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
			ft_execute_and_clear(parser, parser_save, env);
	}
	free(str);
	return (1);
}
