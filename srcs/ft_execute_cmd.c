/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:22:33 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/27 15:22:51 by trbonnes         ###   ########.fr       */
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