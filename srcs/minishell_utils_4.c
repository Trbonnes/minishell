/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:28:13 by trbonnes          #+#    #+#             */
/*   Updated: 2020/02/17 13:07:29 by trbonnes         ###   ########.fr       */
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
