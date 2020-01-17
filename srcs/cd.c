/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:54:45 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/17 17:33:47 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

char	*ft_home(char *str)
{
	char *copy;
	char *strafree;	
	int len;
	const char users[17] = "/Users/trdella-/";

	len = ft_strlen(str);
	if (!(copy = malloc(sizeof(char) * (16 + len + 1))))
		return (NULL);
	strafree = copy;
	if (str[0] == '~')
	copy = ft_strjoin(users, str + 2);	
	else
		copy = ft_strdup(users);
	free(str);
	free(strafree);
	return (copy);
}