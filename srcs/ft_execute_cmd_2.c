/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trbonnes <trbonnes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:29:43 by trbonnes          #+#    #+#             */
/*   Updated: 2020/06/30 09:29:44 by trbonnes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

char		*ft_execute_empty_path(t_parsing *parser)
{
	int			k;
	int			i;
	char		*path;

	k = 0;
	i = 0;
	if (!(path = malloc(sizeof(char) * (ft_strlen(parser->executable)
	+ 3))))
		return (NULL);
	path[k++] = '.';
	path[k++] = '/';
	while (parser->executable[i])
		path[k++] = parser->executable[i++];
	path[k] = '\0';
	return (path);
}
