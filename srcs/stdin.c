/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/17 16:02:31 by trbonnes         ###   ########.fr       */
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
	return (1);
}

int ft_select_builtin(char *cmd_str)
{
	const char * const *builtins = (const char *[]){"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	int i;

	i = -1;
	while (cmd_str[++i])
		cmd_str[i] = ft_tolower(cmd_str[i]);
	i = -1;
	while (builtins[++i] != NULL && ft_strcmp(builtins[i], cmd_str) != 0)
		;
	return(i);
}

int ft_detect_builtin()
{
	int i;
	int j;
	t_parsing parser;
	char *str;
	char *cmd_str;

	i = 0;
	parser = (t_parsing) { 0 };
	write(1,"$>", 2);
	get_next_line(0, &str);
	while(str[i])
	{
		j = 0;
		while(((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) && ++i)
			j++;
		if (!(cmd_str=malloc(sizeof(char) * j + 1)))
			return (-1);
		i = i - j;
		j = 0;
		while((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
			cmd_str[j++] = str[i++];
		cmd_str[j] = '\0';
		parser.builtin_detected = ft_select_builtin(cmd_str);//7 dans le cas d'une commande inconnue
		free(cmd_str);
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i])
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
		ft_execute_builtin(&parser);//Return -1 dans le cas d'une commande inconnue
		printf("%d\n", parser.builtin_detected);
		i++;
	}
	free(str);
	return (1);
}