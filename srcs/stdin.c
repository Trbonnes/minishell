/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/23 10:41:49 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_execute_builtin(t_parsing *parser)
{
	printf("cmd: %d\n", parser->builtin_detected);
	printf("option: %d\n", parser->echo_option);
	printf("param: %s\n", parser->param);
	printf("redirection: %s\n", parser->redirection);
	if (parser->builtin_detected == 7)
		write(2, "minishell: command not found\n", 29);
	else
		find_fd(parser);
	// if (parser->builtin_detected == 0)
	// 	return(/*cd*/1);
	// else if (parser->builtin_detected == 1)
	// 	return(/*echo*/1);
	// else if (parser->builtin_detected == 2)
	// 	return(/*env*/1);
	// else if (parser->builtin_detected == 3)
	// 	return(/*exit*/1);
	// else if (parser->builtin_detected == 4)
	// 	return(/*export*/1);
	// else if (parser->builtin_detected == 5)
	// 	return(/*pwd*/1);
	// else if (parser->builtin_detected == 6)
	// 	return(/*unset*/1);
	return (0);
}

int		ft_select_builtin(char *builtin_str)
{
	int					i;
	const char *const	*builtins = (const char *[]){"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};

	i = -1;
	while (builtin_str[++i])
		builtin_str[i] = ft_tolower(builtin_str[i]);
	i = -1;
	while (builtins[++i] != NULL && ft_strcmp(builtin_str, builtins[i]) != 0)
		;
	return (i);
}

char	*ft_parser_cmd(char *str)
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

int		ft_option(char *str, t_parsing *parser, int i)
{
	if (parser->builtin_detected != 1)
	{
		write(2, "minishell: ", 11);
		write(2, &str[i], 1);
		write(2, &str[++i], 1);
		write(2, ": invalid option\n", 17);
	}
	else if (str[i + 1] == 'n')
	{
		parser->echo_option = 1;
		i += 2;
	}
	return (i);
}

int		ft_detect_builtin(void)
{
	int			i;
	t_parsing	parser;
	char		*str;

	i = 0;
	write(1, "minishell$>", 11);
	get_next_line(0, &str);
	while (str[i])
	{
		parser = (t_parsing) { 0 };
		if ((parser.param = ft_parser_cmd(str + i)) == NULL)
			return (-1);
		i = ft_increment_begin(str, i);
		parser.builtin_detected = ft_select_builtin(parser.param);
		free(parser.param);
		i = ft_increment_option(str, i, &parser);
		if (ft_parser_get(&parser, str, i) == -1)
			return (-1);
		ft_execute_builtin(&parser);
		free(parser.param);
		free(parser.redirection);
		i = ft_increment_end(str, i);
	}
	free(str);
	return (1);
}
