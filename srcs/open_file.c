/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:17:38 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/21 18:44:17 by trdella-         ###   ########.fr       */
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
	&& str[i] != '>' && str[i] != '!' && str[i] != '\0')
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
	int		i;
	char	*copy;

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
	int		i;
	char	*copy;

	if (!(copy = malloc(sizeof(char) * (strlen_word_file(str, 0) + 1))))
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
	&& str[i] != '>' && str[i] != '!' && str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*skip_file(char *str)
{
	int		i;
	char	*copy;
	int		j;

	j = 0;
	if (!(copy = malloc(sizeof(char) * (strlen_word_file(str, 1) + 1))))
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
	&& str[i] != '>' && str[i] != '!' && str[i] != '\0')
		i++;
	while (str[i])
	{
		copy[j] = str[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	free(str);
	return (copy);
}

void	open_file(t_parsing *alk, t_fd *fd)
{
	int		dbchevron;

	dbchevron = 0;
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] == '>')
	{
		if (alk->redirection[1] == '>')
			dbchevron++;
		superior(alk, dbchevron, fd);
	}
	if (alk->redirection[0] == '<')
	{
		if (alk->redirection[1] == '<')
			dbchevron++;
		inferior(alk, dbchevron, fd);
	}
}
