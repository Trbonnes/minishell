/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:46:44 by user42            #+#    #+#             */
/*   Updated: 2020/06/10 16:26:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;

bool	check_error_export_quote(char *str, char c)
{
	int i;

	i = 1;
	while (str[i] && str[i] != c)
	{
		if (str[i] != ' ' && str[i] != '	')
			return (false);
		i++;
	}
	return (true);
}

int		param_refull(t_parsing *alk, char **split, bool *is_error)
{
	int i;
	int j;

	i = -1;
	j = 0;
	free(alk->param);
	while (split[++i])
		if (!is_error[i])
			j += ft_strlen(split[i]);
		else
			display_error_env(alk->builtin_detected, split[i]);
	if (!(alk->param = malloc(sizeof(char *) * j + 1)))
		return (-1);
	return (param_refull_k(alk, split, is_error));
}

void	check_error_export_loop(char **split, bool *is_error, t_parsing *alk)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		if (split[i][j] >= '0' && split[i][j] <= '9')
			is_error[i] = true;
		while (split[i][j] && split[i][j] != '=')
			if (!is_env_var(split[i][j++]))
				is_error[i] = true;
		if (split[i][j] && j != 0)
			j++;
		else if (alk->builtin_detected == 4 && split[i][j] == '=')
			is_error[i] = true;
		else if (alk->builtin_detected == 4)
			is_error[i] = false;
		else if (alk->builtin_detected == 2 && split[i][j] != '=')
			is_error[i] = true;
		j = 0;
		if ((split[i][j] == '"' || split[i][j] == '\'') && ++j)
			is_error[i] = check_error_export_quote(split[i], split[i][j]);
		i++;
	}
}

int		check_error_export(t_parsing *alk, char **split)
{
	int		i;
	int		j;
	bool	*is_error;

	i = 0;
	j = 0;
	while (split[i++])
		;
	if (!(is_error = malloc(sizeof(bool) * i + 1)))
		return (-1);
	while (j <= i)
		is_error[j++] = false;
	check_error_export_loop(split, is_error, alk);
	if (alk->builtin_detected == 2)
		if (check_is_error_env(alk, split, is_error, i) == -1)
		{
			g_last_return_value = 127;
			return (-1);
		}
	return (param_refull(alk, split, is_error));
}

int		error_message_builtin(t_parsing *alk)
{
	char	**split;

	g_last_return_value = 0;
	if (alk->builtin_detected == 2 && alk->param[0] != '\0')
	{
		split = ft_split_export(alk->param);
		return (check_error_export(alk, split));
	}
	if (alk->builtin_detected == 4 && alk->param[0] != '\0')
	{
		split = ft_split_export(alk->param);
		return (check_error_export(alk, split));
	}
	if (alk->builtin_detected == 6 && alk->param[0] != '\0')
		return (check_error_unset(alk));
	return (0);
}
