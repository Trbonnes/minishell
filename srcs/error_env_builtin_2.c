/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:25:41 by user42            #+#    #+#             */
/*   Updated: 2020/06/10 16:26:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;

void	check_error_unset_loop(char **split, bool *is_error)
{
	int i;
	int j;

	i = 0;
	while (split[i])
	{
		j = 0;
		if ((split[i][j] == '"' || split[i][j] == '\'') && ++j)
			is_error[i] = check_error_export_quote(split[i], split[i][j]);
		if (split[i][j] >= '0' && split[i][j] <= '9')
			is_error[i] = true;
		while (split[i][j])
			if (!is_env_var(split[i][j++]))
				is_error[i] = true;
		i++;
	}
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
	if (!(is_error = malloc(sizeof(bool) * i + 1)))
		return (-1);
	while (j <= i)
		is_error[j++] = false;
	check_error_unset_loop(split, is_error);
	return (param_refull(alk, split, is_error));
}
