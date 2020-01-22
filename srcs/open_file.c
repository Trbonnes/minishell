/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:17:38 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/22 20:47:16 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		strlen_word_file(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
	&& str[i] != '>' && str[i] != '!' && str[i] != '\0')
		i++;
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
	char	c;
	
	i = 0;
	if (!(copy = malloc(sizeof(char) * (strlen_word_file(str) + 1))))
		return (NULL);
	if (str[i] == '\'' || str[i] == '"')
	{
		c = str[i];
		while(str[i + 1] != c && str[i + 1] != '\0')
		{
			copy[i] = str[i + 1];
			i++;
		}
	}
	else
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
	int		len;
	char	c;
	
	i = 0;
	len = ft_strlen(str);
	if (str[i] == '\'' || str[i] == '"')
	{
		c = str[i];
		i++;
		while(str[i] != c && str[i] != '\0')
			i++;
		i++;
	}
	else
		while (str[i] != ' ' && str[i] != ';' && str[i] != '<'
		&& str[i] != '>' && str[i] != '!' && str[i] != '\0' && str[i] != '\'' && str[i] != '"')
			i++;
	copy = ft_substr(str, i, len - i);
	free(str);
	return (copy);
}

int		open_file(t_parsing *alk, t_fd *fd)
{
	int		dbchevron;
	int		ret;

	ret = 0;
	dbchevron = 0;
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] == '>')
	{
		if (alk->redirection[1] == '>')
			dbchevron++;
		ret = superior(alk, dbchevron, fd);
	}
	else if (alk->redirection[0] == '<')
	{
		if (alk->redirection[1] == '<')
			dbchevron++;
		ret = inferior(alk, dbchevron, fd);
	}
	return (ret);
}
