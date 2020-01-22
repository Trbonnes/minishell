/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/22 16:49:47 by trbonnes         ###   ########.fr       */
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

int		ft_redirection_setup(char *str, char **actual)
{
	int		i;
	int		j;
	char	*redirection;
	char	*tmp;
	char	*quote_str;

	i = 0;
	j = -1;
	tmp = NULL;
	quote_str = NULL;
	if (actual[0])
		tmp = ft_strdup(actual[0]);
	free(actual[0]);
	i = ft_redirection_calculate(i, &str, &quote_str);
	if (!(redirection = malloc(sizeof(char) * i + 1)))
		return (-1);
	while (++j < i && str[j])
		redirection[j] = str[j];
	if (j < i)
	{
		i = 0;
		while (quote_str[i])
			redirection[j++] = quote_str[i++];
	}
	redirection[j] = '\0';
	actual[0] = ft_strjoin(tmp, redirection);
	free(tmp);
	free(redirection);
	free(quote_str);
	return (j);
}

char	*ft_realloc_param_str(int i, int j, char *param_str)
{
	int		k;
	char	*cpy;

	if ((size_t)(i + j) > ft_strlen(param_str))
		k = i;
	else
		k = ft_strlen(param_str) - j;
	if (!(cpy = malloc(sizeof(char) * k + 1)))
		return (NULL);
	ft_bzero(cpy, k + 1);
	k = -1;
	while (++k < i)
		cpy[k] = param_str[k];
	i += j;
	while (param_str[i])
		cpy[k++] = param_str[i++];
	free(param_str);
	return (cpy);
}

char	*ft_parser_redirection(char **builtin_str)
{
	int		i;
	int		j;
	int		quote;
	char	*redirection_str;

	i = -1;
	redirection_str = NULL;
	quote = 0;
	while (builtin_str[0][++i])
	{
		if (builtin_str[0][i] == 34)
		{
			if (quote == 0)
				quote = 34;
			else if (quote == 34)
				quote = 0;
		}
		if (builtin_str[0][i] == 39)
		{
			if (quote == 0)
				quote = 39;
			else if (quote == 39)
				quote = 0;
		}
		if ((builtin_str[0][i] == '<' || builtin_str[0][i] == '>') && quote == 0)
		{
			j = ft_redirection_setup(builtin_str[0] + i, &redirection_str);
			builtin_str[0] = ft_realloc_param_str(i, j, builtin_str[0]);
			i = -1;
		}
	}
	if (quote != 0)
		ft_wait_quote(quote, builtin_str);
	if (!redirection_str)
	{
		if (!(redirection_str = malloc(sizeof(char) * 1)))
			return (NULL);
		redirection_str[0] = '\0';
	}
	ft_unquote(builtin_str);
	return (redirection_str);
}

char	*ft_parser_param(char *str)
{
	char	*parsed;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != ';' && str[i] != '|' && ++i)
		j++;
	if (!(parsed = malloc(sizeof(char) * j + 1)))
		return (NULL);
	i = i - j;
	j = 0;
	while (str[i] && str[i] != ';' && str[i] != '|')
		parsed[j++] = str[i++];
	parsed[j] = '\0';
	return (parsed);
}

int		ft_option(char *str, t_parsing	*parser, int i)
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
	parser = (t_parsing) { 0 };
	write(1, "minishell$>", 11);
	get_next_line(0, &str);
	while (str[i])
	{
		if ((parser.param = ft_parser_cmd(str + i)) == NULL)
			return (-1);
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ' && str[i] != ';'
		&& str[i] != '|' && str[i] != '<' && str[i] != '>')
			i++;
		parser.builtin_detected = ft_select_builtin(parser.param);
		free(parser.param);
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i] && parser.builtin_detected < 7)
			i = ft_option(str, &parser, i);
		if ((parser.param = ft_parser_param(str + i)) == NULL)
			return (-1);
		if ((parser.redirection = ft_parser_redirection(&parser.param)) == NULL)
			return (-1);
		ft_execute_builtin(&parser);
		free(parser.param);
		free(parser.redirection);
		while (str[i] != '\0' && str[i] != ';' && str[i] != '|')
			i++;
		if (str[i] != '\0')
			i++;
		parser = (t_parsing) { 0 };
	}
	free(str);
	return (1);
}
