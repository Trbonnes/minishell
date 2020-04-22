/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:46:44 by user42            #+#    #+#             */
/*   Updated: 2020/04/22 19:03:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int     is_env_var(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (-1);
}

int		error_message_builtin(t_parsing *alk)
{
	int		i;
	int		j;
	char	**split;
	bool	*is_error;
	bool	into_q;
	bool	error;

	i = 0;
	j = 0;
	into_q = false;
	error = false;
	split = ft_split(alk->param, ' ', " = ");
	while (split[i++])
		;
	is_error = malloc(sizeof(bool) * i);
	while (j <= i)
		is_error[j++] = false;
	if (alk->builtin_detected == 2 && alk->param[0] != '\0')
	{
			ft_putstr("env");
			write(1, ": ", 2);
			ft_putstr(alk->param);
			write(1, ": no such file or directory\n", 29);
			return (-1);
	}
	if (alk->builtin_detected == 4)
	{
		while (split[i])
		{
			j = 0;
			while(split[i][j] && split [i][j] != '=')
				if (!is_env_var(split[i][j++]))
					error = true;
			j++;
			while(split[i][j])
				if (!is_env_var(split[i][j++]))
					error = true;
			if (error)
				is_error[i] = true;
			i++;
		}
		free(alk->param);
		i = 0;
		j = 0;
		while (split[i])
		{
			if (!is_error)
				j += ft_strlen(split[i]);
			i++;
		}
		
	}

	if (alk->param[0] != '\0')
	{
		if (alk->builtin_detected == 2)
			ft_putstr("env");
		if (alk->builtin_detected == 4)
			ft_putstr("export");
		if (alk->builtin_detected == 6)
			ft_putstr("unset");
		write(1, ": ", 2);
		ft_putstr(alk->param);
		write(1, ": no such file or directory\n", 29);
	}
}
