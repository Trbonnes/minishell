/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:46:44 by user42            #+#    #+#             */
/*   Updated: 2020/04/22 20:35:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int     is_env_var(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int		error_message_builtin(t_parsing *alk)
{
	int		i;
	int		j;
	int		k;
	char	**split;
	bool	*is_error;

	i = 0;
	j = 0;
	k = 0;
	if (alk->builtin_detected == 2 && alk->param[0] != '\0')
	{
			ft_putstr("env");
			write(1, ": ", 2);
			ft_putstr(alk->param);
			write(1, ": no such file or directory\n", 29);
			return (-1);
	}
	if (alk->builtin_detected == 4 && alk->param[0] != '\0')
	{
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
			while(split[i][j] && split [i][j] != '=')
				if (!is_env_var(split[i][j++]))
					is_error[i] = true;
			if (split[i][j] && j != 0)
				j++;
			else
				is_error[i] = true;
			while(split[i][j])
				if (!is_env_var(split[i][j++]))
					is_error[i] = true;
			i++;
		}
		free(alk->param);
		i = 0;
		j = 0;
		while (split[i])
		{
			if (!is_error[i])
				j += ft_strlen(split[i]);
			else
			{
				ft_putstr("export");
				write(1, ": ", 2);
				ft_putstr(split[i]);
				write(1, ": no such file or directory\n", 29);
			}
			i++;
		}
		alk->param = malloc(sizeof(char *) * j + 1);
		i = 0;
		while (split[i])
		{
			j = 0;
			if (!is_error[i])
			{
				while (split[i][j])
					alk->param[k++] = split[i][j++];
				alk->param[k++] = ' ';
			}
			i++;
		}
		alk->param[k] = '\0';
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		free(is_error);
		if (k == 0)
			return (-1);
	}

	if (alk->builtin_detected == 6 && alk->param[0] != '\0')
	{
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
			while(split[i][j])
				if (!is_env_var(split[i][j++]))
					is_error[i] = true;
			i++;
		}
		free(alk->param);
		i = 0;
		j = 0;
		while (split[i])
		{
			if (!is_error[i])
				j += ft_strlen(split[i]) + 1;
			else
			{
				ft_putstr("export");
				write(1, ": ", 2);
				ft_putstr(split[i]);
				write(1, ": no such file or directory\n", 29);
			}
			i++;
		}
		alk->param = malloc(sizeof(char *) * j + 1);
		i = 0;
		while (split[i])
		{
			j = 0;
			if (!is_error[i])
			{
				while (split[i][j])
					alk->param[k++] = split[i][j++];
				alk->param[k++] = ' ';
			}
			i++;
		}
		alk->param[k] = '\0';
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		free(is_error);
		if (k == 0)
			return (-1);
	}
	return (0);
}
