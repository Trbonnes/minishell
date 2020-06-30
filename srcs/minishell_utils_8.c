/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:32:56 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:32:56 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int			execute_and_clear_r(char *str, t_parsing *parser,
t_parsing *parser_save, char **env)
{
	if (ft_execute_and_clear(parser, parser_save, env) == -1)
	{
		free(str);
		return (-1);
	}
	return (0);
}

char		*init_pipe_error(t_parsing **parser, t_parsing **parser_save)
{
	parser[0]->next = NULL;
	parser[0]->param = NULL;
	parser[0]->redirection = NULL;
	parser[0]->executable = NULL;
	ft_parserclear(parser_save);
	return (NULL);
}

int			ft_command_not_found(t_parsing *alk)
{
	write(2, "minishell: ", 11);
	write(2, alk->executable, ft_strlen(alk->executable));
	write(2, ": command not found\n", 20);
	exit(127);
	return (-1);
}

int			ft_no_such_file(t_parsing *alk)
{
	write(2, "minishell: ", 11);
	write(2, alk->executable, ft_strlen(alk->executable));
	write(2, ": No such file or directory\n", 28);
	exit(127);
	return (-1);
}

char		*ft_pipe_null_return(char *buffer, char *str)
{
	free(buffer);
	free(str);
	return (NULL);
}
