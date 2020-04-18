/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:28:13 by trbonnes          #+#    #+#             */
/*   Updated: 2020/04/18 15:05:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env	*g_env_list;

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

int		last_return_setup(int status)
{
	int last_return_value;

	last_return_value = status;
	if (status == 2)
		last_return_value = 130;
	else if (status == 3)
		last_return_value = 131;
	else if (status == 32512)
		last_return_value = 127;
	else if (status == 65280)
		last_return_value = 255;
	else if (status == 512)
		last_return_value = 2;
	else if (status == 256)
		last_return_value = 1;
	else if (status == 33280)
		last_return_value = 1;
	return (last_return_value);
}

int		chevron_error(void)
{
	write(2,
	"minishell: syntax error near unexpected token `newline'\n", 56);
	g_last_return_value = 2;
	return (-1);
}

int		ft_ref_len(t_env *search)
{
	int		j;
	int		k;

	j = 0;
	k = 1;
	while (search->ref[k - 1] != '=')
		k++;
	while (search->ref[k + j])
		j++;
	return (j);
}
