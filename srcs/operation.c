/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/20 13:28:41 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		find_fd(t_parsing *alk)
{
	int fd;
	
	if (alk->builtin_detected == 0)
		ft_cd(alk->redirection);
	if (alk->builtin_detected == 1)
	{
		fd = open_echo(alk->redirection, 1);
		printf("param = %s\nfd = %d\n", alk->param, fd);
		ft_echo(alk->param, fd, alk->echo_option);
		close(fd);
	}
	
	return (0);
}