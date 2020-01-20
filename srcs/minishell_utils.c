/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:01:40 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/20 15:25:14 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

char	*ft_strjoin(const char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	x;
	char	*copy;

	i = 0;
	j = 0;
	x = -1;
	if (s1)
		while (s1[i])
			i++;
	while (s2[j])
		j++;
	if ((copy = (char *)malloc(i + j + 1)) == NULL)
		return (NULL);
	while (++x < i)
		copy[x] = s1[x];
	x = -1;
	while (++x < j)
		copy[i + x] = s2[x];
	copy[i + j] = '\0';
	return (copy);
}


size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char *copy;
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	if (!(copy = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_whitespace(char *str)
{
	int i;
	char *copy;
	
	i = 0;
	while (str[i] == ' ')
		i++;
	if (!(copy = ft_strdup(str + i)))
		return (NULL);
	free(str);
	return (copy);
}