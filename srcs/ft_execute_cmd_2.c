/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:12:36 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 15:13:02 by user42           ###   ########.fr       */
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