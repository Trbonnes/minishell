/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/20 11:42:01 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_execute_builtin(t_parsing *parser)
{
	printf("cmd: %d\n", parser->builtin_detected);
	printf("option: %d\n", parser->echo_option);
	printf("param: %s\n", parser->param);
	printf("redirection: %s\n", parser->redirection);
	if (parser->builtin_detected == 0)
		return(/*cd*/1);
	else if (parser->builtin_detected == 1)
		return(/*echo*/1);
	else if (parser->builtin_detected == 2)
		return(/*env*/1);
	else if (parser->builtin_detected == 3)
		return(/*exit*/1);
	else if (parser->builtin_detected == 4)
		return(/*export*/1);
	else if (parser->builtin_detected == 5)
		return(/*pwd*/1);
	else if (parser->builtin_detected == 6)
		return(/*unset*/1);
	write(2, "bash: command not found\n", 24);
	return (0);
}

int ft_select_builtin(char *builtin_str)
{
	const char * const *builtins = (const char *[]){"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	int i;

	i = -1;
	while (builtin_str[++i])
		builtin_str[i] = ft_tolower(builtin_str[i]);
	i = -1;
	while (builtins[++i] != NULL && ft_strcmp(builtin_str, builtins[i]) != 0)
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
	if (!(parsed = malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|' && str[i] != '<' && str[i] != '>')
		parsed[j++] = str[i++];
	parsed[j] = '\0';
	return (parsed);
}

char *redirection_alloc(int len, char *str)
{
	int		i;
	char	*redirection_str;
	char	*tmp;

	tmp = NULL;
	i = 0;
	printf("before: %s\n", str);
	if(str)
	{
		while (str[i])
			i++;
		if ((tmp = malloc(sizeof(char) * i + 1)) == NULL)
			return (NULL);
		i = -1;
		while (str[++i])
			tmp[i] = str[i];
		tmp[i] = '\0';
		free(str);
	}
	if ((redirection_str = malloc(sizeof(char) * len + i + 1)) == NULL)
			return (NULL);
	i = -1;
	while(++i && tmp[i])
		redirection_str[i] = tmp[i];
	redirection_str[i] = '\0';
	free(tmp);
	printf("after: %s\n", redirection_str);
	return (redirection_str);
}

char *ft_parser_redirection(char **builtin_str)
{
	int i;
	int j;
	int len;
	char *redirection_str;

	i = 0;
	j = 0;
	redirection_str = NULL;
	while (builtin_str[0][i] && builtin_str[0][i] != ';' && builtin_str[0][i] != '|')
	{
		len = 0;
		while (builtin_str[0][i] && builtin_str[0][i] != '<' && builtin_str[0][i] != '>')
			i++;
		while (builtin_str[0][i + len] && (builtin_str[0][i + len] == '<' || builtin_str[0][i + len] == '>' || builtin_str[0][i + len] == ' '))
			len++;
		while (builtin_str[0][i + len] && builtin_str[0][i + len] != ' ' && builtin_str[0][i + len] != ';' && builtin_str[0][i + len] != '|' && builtin_str[0][i + len] != '<' && builtin_str[0][i + len] != '>')
			len++;
		printf("len: %d\n", len);
		if ((redirection_str = redirection_alloc(len, redirection_str)) == NULL)
			return (NULL);
		len += i;
		while (i <= len)
		{
			printf("C: %c\n", builtin_str[0][i]);
			redirection_str[j++] = builtin_str[0][i++];
		}
		redirection_str[j] = '\0';
	}
	if(!redirection_str)
	{
		printf("NULL\n");
		if ((redirection_str = malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		redirection_str[0] = '0';
		redirection_str[0] = '\0';
	}
	printf("redirection_str: %s\n", redirection_str);
	return (redirection_str);
}

char *ft_parser_param(char *str)
{
	char *parsed;
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] /*&& str[i] != ' '*/ && str[i] != ';' && str[i] != '|' && ++i)
		j++;
	if (!(parsed = malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] /*&& str[i] != ' '*/ && str[i] != ';' && str[i] != '|')
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
	while (str[++i])
	{
		if ((parser.param = ft_parser_cmd(str + i)) == NULL)
			return (-1);
		printf("cmd: %s\n", parser.param);
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
		while (str[i] /*&& str[i] != ' '*/ && str[i] != ';' && str[i] != '|')
			i++;
		if ((parser.redirection = ft_parser_redirection(&parser.param)) == NULL)
			return (-1);
		printf("builtin executed: %d\n", ft_execute_builtin(&parser));//Return -1 dans le cas d'une commande inconnue
		free(parser.param);
		free(parser.redirection);
		if (str[i] != '\0')
			i++;
	}
	free(str);
	printf("End of command\n");
	return (1);
}