/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/17 17:53:44 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_execute_builtin(t_parsing *parser)
{
	if (parser->builtin_detected == 0)
		return(/*cd*/0);
	else if (parser->builtin_detected == 1)
		return(/*echo*/0);
	else if (parser->builtin_detected == 2)
		return(/*env*/0);
	else if (parser->builtin_detected == 3)
		return(/*exit*/0);
	else if (parser->builtin_detected == 4)
		return(/*export*/0);
	else if (parser->builtin_detected == 5)
		return(/*pwd*/0);
	else if (parser->builtin_detected == 6)
		return(/*unset*/0);
	write(2, "bash: command not found\n", 24);
	return (1);
}

int ft_select_builtin(char *builtin_str)
{
	const char * const *builtins = (const char *[]){"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	int i;

	i = -1;
	while (builtin_str[++i])
		builtin_str[i] = ft_tolower(builtin_str[i]);
	i = -1;
	while (builtins[++i] != NULL && ft_strcmp(builtins[i], builtin_str) != 0)
		;
	return(i);
}

char *ft_parser_cmd(char *str)
{
	char *parsed;
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|' && str[i] != '<' && str[i] != '>' && ++i)
		j++;
	if (!(parsed=malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|' && str[i] != '<' && str[i] != '>')
		parsed[j++] = str[i++];
	parsed[j] = '\0';
	return (parsed);
}

char *ft_parser_redirection(char **builtin_str)
{
	int i;
	int j;
	int len;
	char *redirection_str;

	i = 0;
	len = 0;
	j = 0;
	while (builtin_str[0][i] && builtin_str[0][i] != '<' && builtin_str[0][i] != '>')
		i++;
	while (builtin_str[0][i + len] && builtin_str[0][i + len] == '<' && builtin_str[0][i + len] == '>' && builtin_str[0][i + len] == ' ')
		len++;
	while (builtin_str[0][i + len] && builtin_str[0][i + len] != ' ' && builtin_str[0][i + len] != ';' && builtin_str[0][i + len] != '|' && builtin_str[0][i + len] != '<' && builtin_str[0][i + len] != '>')
		len++;
	if ((redirection_str = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (i <= len)
		redirection_str[j++] = builtin_str[0][i++];
	redirection_str[j] = '\0';
	return (redirection_str);
}

char *ft_parser_param(char *str)
{
	char *parsed;
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|' && ++i)
		j++;
	if (!(parsed=malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|')
		parsed[j++] = str[i++];
	parsed[j] = '\0';
	return (parsed);
}


int ft_detect_builtin()
{
	int i;
	t_parsing parser;
	char *str;

	i = -1;
	parser = (t_parsing) { 0 };
	write(1,"$>", 2);
	get_next_line(0, &str);
	while(str[++i])
	{
		if ((parser.param = ft_parser_cmd(str + i)) == NULL)
			return (-1);
		while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|' && str[i] != '<' && str[i] != '>')
			i++;
		parser.builtin_detected = ft_select_builtin(parser.param);//7 dans le cas d'une commande inconnue
		free(parser.param);
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i] && parser.builtin_detected < 7)
		{
			if(parser.builtin_detected != 1)
			{
				write(2, "bash: ", 6);
				write(2, &str[i], 1);
				write(2, &str[++i], 1);
				write(2, ": invalid option\n", 17);
			}
			else if (str[i + 1] == 'n')
			{
				parser.echo_option = 1;
				i += 2;
			}
		}
		if ((parser.param = ft_parser_param(str + i)) == NULL)
			return (-1);
		while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|')
			i++;
		if ((parser.redirection = ft_parser_redirection(&parser.param)) == NULL)
			return (-1);
		ft_execute_builtin(&parser);//Return -1 dans le cas d'une commande inconnue
		printf("%d\n", parser.builtin_detected);
		free(parser.param);
		free(parser.redirection);
		if (str[i] != '\0')
			i++;
	}
	free(str);
	return (1);
}