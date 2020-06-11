/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_env_builtin_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:25:41 by user42            #+#    #+#             */
/*   Updated: 2020/06/11 15:19:03 by user42           ###   ########.fr       */
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

int		ft_print_syntax_error(char *str, int i)
{
	g_last_return_value = 2;
	write(2, "syntax error near unexpected token ", 35);
	write(2, &str[i], 1);
	write(2, "\n", 1);
	free(str);
	return (1);
}

int		ft_syntax_error_spaces(char *str)
{
	int		i;
	bool	detected;

	i = -1;
	detected = false;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '	')
			detected = true;
	if (!detected)
	{
		free(str);
		return (1);
	}
	return (0);
}

int		ft_syntax_error_comma(char *str)
{
	int		i;
	bool	detected;

	i = 0;
	while (str[i])
	{
		detected = false;
		while (str[i] && str[i] != ';' && str[i] != '|')
		{
			if (str[i] == '\\' && (str[i + 1] == ';' || str[i + 1] == '|'))
				i += 2;
			if (str[i] != ' ' && str[i] != '	')
				detected = true;
			if (str[i])
				i++;
		}
		if (str[i] && detected == false)
			return (ft_print_syntax_error(str, i));
		else if (str[i])
			i++;
	}
	return (ft_syntax_error_spaces(str));
}
