/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:26:25 by trbonnes          #+#    #+#             */
/*   Updated: 2020/01/21 17:21:25 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int main(int ac, char **av, char **env)
{
	(void)(ac + av);
	(void)env; //parser en liste chainee
	while(ft_detect_builtin() > 0)
		printf("Command Executed\n");
	return (0);
}