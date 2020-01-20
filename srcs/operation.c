/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/20 14:52:24 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		find_fd(t_parsing *alk)
{
	int fd;
	
	fd = open_echo(alk->redirection, 1);
	if (alk->builtin_detected == 0)
		ft_cd(alk->redirection);
	if (alk->builtin_detected == 1)
	{
		ft_echo(alk->param, fd, alk->echo_option);
		close(fd);
	}
	
	return (0);
}