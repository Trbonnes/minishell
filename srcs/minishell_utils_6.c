/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 16:47:53 by user42            #+#    #+#             */
/*   Updated: 2020/04/28 14:28:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		is_env_var(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9') || c == '_' || c == '\'' || c == '\"')
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

void	ft_check_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == 26)
			split[i][0] = '\0';
		i++;
	}
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

int		check_is_error_env(t_parsing *alk, char **split,
bool *is_error, int i)
{
	int	j;

	j = -1;
	while (++j <= i)
		if (is_error[j])
		{
			display_error_env(alk->builtin_detected, split[j]);
			j = 0;
			while (split[j])
				free(split[j++]);
			free(split);
			free(is_error);
			return (-1);
		}
	return (0);
}
