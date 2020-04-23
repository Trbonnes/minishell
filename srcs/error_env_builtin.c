/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:46:44 by user42            #+#    #+#             */
/*   Updated: 2020/04/23 14:02:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		is_env_var(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

void	display_error_env(int builtin, char *param_str)
{
	if (builtin == 2)
		ft_putstr("env");
	if (builtin == 4)
		ft_putstr("export");
	if (builtin == 6)
		ft_putstr("unset");
	write(1, ": ", 2);
	ft_putstr(param_str);
	write(1, ": no such file or directory\n", 29);
}

int		param_refull_k(t_parsing *alk, char **split, bool *is_error)
{
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	while (split[++i])
	{
		j = 0;
		if (!is_error[i])
		{
			while (split[i][j])
				alk->param[k++] = split[i][j++];
			alk->param[k++] = ' ';
		}
	}
	alk->param[k] = '\0';
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(is_error);
	if (k == 0)
		return (-1);
	return (0);
}

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
			if (!is_env_var(split[i][j++]))
				is_error[i] = true;
		i++;
	}
}

int		check_error_export(t_parsing *alk)
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
	if (!(is_error = malloc(sizeof(bool) * i + 1)))
		return (-1);
	while (j <= i)
		is_error[j++] = false;
	check_error_export_loop(split, is_error);
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
	if (alk->builtin_detected == 2 && alk->param[0] != '\0')
	{
		display_error_env(alk->builtin_detected, alk->param);
		return (-1);
	}
	if (alk->builtin_detected == 4 && alk->param[0] != '\0')
		return (check_error_export(alk));
	if (alk->builtin_detected == 6 && alk->param[0] != '\0')
		return (check_error_unset(alk));
	return (0);
}
