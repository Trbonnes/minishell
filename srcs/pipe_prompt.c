/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 15:00:30 by user42            #+#    #+#             */
/*   Updated: 2020/05/20 15:56:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;

char		*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char		*ft_strcpy(char *dest, char *src)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

int			ft_pipe_prompt_check(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	if (buffer[0] == 3)
	{
		write(2, "minishell: unexpected end of file\n", 34);
		g_last_return_value = 2;
		return (1);
	}
	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '	'))
		i++;
	if (buffer[i] == '\0')
		return (0);
	return (1);
}

char		*ft_pipe_prompt(char *buffer)
{
	int j;

	j = 0;
	if (buffer)
		while (buffer[j])
			buffer[j++] = '\0';
	write(1, "pipe>", 5);
	get_next_line(0, &buffer);
	return (buffer);
}

char		*ft_increment_pipe(char *str, int i)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	i++;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	if (str[i] == '\0')
	{
		while (ft_pipe_prompt_check(buffer) != 1)
			buffer = ft_pipe_prompt(buffer);
		if (buffer[0] == 3)
			return (ft_pipe_null_return(buffer, str));
		if (!(tmp = malloc(sizeof(char) * (ft_strlen(str)
		+ ft_strlen(buffer) + 1))))
			return (str);
		tmp = ft_strcpy(tmp, str);
		tmp = ft_strcat(tmp, buffer);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		free(buffer);
	}
	return (str);
}
