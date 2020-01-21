/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:54:45 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/21 18:25:24 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"



void	ft_home(t_parsing *alk)
{
	const char users[17] = "/Users/trdella-/";

	if (alk->param[0] == '~')
		alk->param = ft_strjoin(users, alk->param + 2);
	else
		alk->param = ft_strdup(users);
}