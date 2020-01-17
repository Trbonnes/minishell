/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:37:02 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/17 14:49:09 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		parser.builtin_detected = ft_select_builtin(cmd_str);
		free(cmd_str);
	}
	free(str);
	return (1);
}