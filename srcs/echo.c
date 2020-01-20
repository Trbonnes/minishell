/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:17:38 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/20 13:41:11 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		strlen_word_file(char *str, int fileorstr)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
	&& str[i] != '>' &&  str[i] != '!' && str[i] != '\0')
		i++;
	if (fileorstr == 1)
	{
		while (str[i])
		{
			i++;
			j++;
		}
		return (j);
	}
	return (i);
}

char	*skip_operation(char *str)
{
	int i;
	char *copy;
	
	i = 0;
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
			i++;
	}
		if (str[i] == '<')
	{
		i++;
		if (str[i] == '<')
			i++;
	}
	copy = ft_strdup(str + i);
	free(str);
	return (copy);
}

char	*file_name(char *str)
{
	int i;
	char *copy;
	
	if (!(copy = malloc(sizeof(char) * (strlen_word_file(str, 0) + 1))))
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
	&& str[i] != '>' &&  str[i] != '!' && str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*skip_file(char *str)
{
	int i;
	char *copy;
	int j;
	
	j = 0;
	if (!(copy = malloc(sizeof(char) * (strlen_word_file(str, 1) + 1))))
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
	&& str[i] != '>' &&  str[i] != '!' && str[i] != '\0')
		i++;
	while (str[i])
	{
		copy[j] = str[i];
		i++;
		j++;
	}
	copy[i] = '\0';
	free(str);
	return (copy);
}

int		open_echo(char *str, int fd)
{
	char *fd_open;
	int dbchevron;
	
	dbchevron = 0;
	str = ft_whitespace(str);
	if (str[0] == '>')
	{
		if (str[1] == '>')
			dbchevron++;
		str = skip_operation(str);
		str = ft_whitespace(str);
		fd_open = file_name(str);
		str = skip_file(str);
		printf("db = %d\n", dbchevron);
		if (dbchevron == 0)
			fd = open(fd_open, O_WRONLY | O_CREAT, S_IRWXU);
		else
			fd = open(fd_open, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		printf("file = %s et fd = %d\n", fd_open, fd);
		str = ft_whitespace(str);
		if (str[0] != '\0')
		{
			close(fd);
			fd = open_echo(str, fd);
		}
		else
			return (fd);
	}
	return (fd);
}