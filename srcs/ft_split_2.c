/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:04:22 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/01 04:03:22 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		**ft_no_args(void)
{
	char **tab;

	if (!(tab = malloc(sizeof(char*) * 2)))
		return (NULL);
	if (!(tab[0] = malloc(sizeof(char*) * 1)))
		return (NULL);
	tab[0][0] = '\0';
	tab[1] = 0;
	return (tab);
}
