/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:46:44 by user42            #+#    #+#             */
/*   Updated: 2020/04/24 19:43:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		param_refull(t_parsing *alk, char **split, bool *is_error)
{
	int i;
	int j;

	i = 0;
	j = 0;
	free(alk->param);
	while (split[i])
	{
		if (!is_error[i])
			j += ft_strlen(split[i]);
		else
			display_error_env(alk->builtin_detected, split[i]);
		i++;
	}
	if (!(alk->param = malloc(sizeof(char *) * j + 1)))
		return (-1);
	return (param_refull_k(alk, split, is_error));
}

void	check_error_export_loop(char **split, bool *is_error)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j] && split[i][j] != '=')
			if (!is_env_var(split[i][j++]))
				is_error[i] = true;
		if (split[i][j] && j != 0)
			j++;
		else
			is_error[i] = true;
		while (split[i][j])
		{
			if (!is_env_var(split[i][j]) && split[i][j] != ' ')
				is_error[i] = true;
			j++;
		}
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
	check_error_export_loop(split, is_error);
	if (alk->builtin_detected == 2)
		if (check_is_error_env(alk, split, is_error, i) == -1)
			return (-1);
	return (param_refull(alk, split, is_error));
}

int		check_error_unset(t_parsing *alk)
{
	int		i;
	int		j;
	char	**split;
	bool	*is_error;

	i = 0;
	j = 0;
	split = ft_split_libft(alk->param, ' ');
	while (split[i++])
		;
	is_error = malloc(sizeof(bool) * i + 1);
	while (j <= i)
		is_error[j++] = false;
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
			if (!is_env_var(split[i][j++]))
				is_error[i] = true;
		i++;
	}
	return (param_refull(alk, split, is_error));
}

int		error_message_builtin(t_parsing *alk)
{
	char	**split;

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
