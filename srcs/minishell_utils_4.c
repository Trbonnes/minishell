/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:28:13 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/18 09:12:35 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env *g_env_list;

void	ft_export_loop(t_fd *fd, t_env *g_env_list)
{
	int len;

	len = ft_strlen(g_env_list->ref);
	if (g_env_list->ref[0] != '\0')
	{
		write(fd->out, "declare -x ", 11);
		write(fd->out, g_env_list->ref, len);
		write(fd->out, "\n", 1);
	}
}

int		ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}

int		last_return_setup(int status)
{
	int last_return_value;

	last_return_value = status;
	if (status == 2)
		last_return_value = 130;
	if (status == 3)
		last_return_value = 131;
	if (status == 32512)
		last_return_value = 127;
	if (status == 65280)
		last_return_value = 255;
	return (last_return_value);
}
