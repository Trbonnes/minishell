/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:10:02 by trdella-          #+#    #+#             */
/*   Updated: 2020/02/13 08:18:42 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern t_env	*g_env_list;

char	*ft_word(t_parsing *alk, int i)
{
	char *word;
	char *ret;
	int j;
	t_env *tmp;

	tmp = g_env_list;
	j = 0;
	while (alk->param[i] != ' ' && alk->param[i] != '\n' && alk->param[i] != '\0')
	{
		i++;
		j++;
	}
	if (!(word = malloc(sizeof(char) * j)))
		return (NULL);
	word = ft_substr(alk->param, i + 1 - j, j);
	printf("word = %s\n", word);
	while (ft_strcmp(word, g_env_list->key) != 0)
		g_env_list = g_env_list->next;
	if (ft_strcmp("HOME", g_env_list->key) != 0)
		return ("");
	ret = g_env_list->ref + j + 1;
	free(word);
	g_env_list = tmp;
	return (ret);
}


int		ft_check_env(t_parsing *alk)
{
	int		i;
	char	*word;

	i = 0;
	while (alk->param[i])
	{
		if (alk->param[i] == '$')
		{
			word = ft_word(alk, i);
			printf("%s\n",word);
		}
		i++;
	}
	return (0);
}

int		superior(t_parsing *alk, int dbchevron, t_fd *fd)
{
	char *fd_open;

	alk->redirection = skip_operation(alk->redirection);
	alk->redirection = ft_whitespace(alk->redirection);
	fd_open = file_name(alk->redirection);
	alk->redirection = skip_file(alk->redirection);
	if (fd->out != 1)
		close(fd->out);
	if (dbchevron == 0)
		fd->out = open(fd_open, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else
		fd->out = open(fd_open, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	free(fd_open);
	if (fd->out == -1)
	{
		ft_putstr(strerror(errno));
		return (-1);
	}
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] != '\0')
		open_file(alk, fd);
	return (0);
}

int		inferior(t_parsing *alk, int dbchevron, t_fd *fd)
{
	char *fd_open;

	alk->redirection = skip_operation(alk->redirection);
	alk->redirection = ft_whitespace(alk->redirection);
	fd_open = file_name(alk->redirection);
	alk->redirection = skip_file(alk->redirection);
	if (fd->in != 0)
		close(fd->in);
	if (dbchevron == 0)
		fd->in = open(fd_open, O_RDONLY | O_APPEND);
	free(fd_open);
	if (fd->in == -1)
	{
		ft_putstr(strerror(errno));
		return (-1);
	}
	alk->redirection = ft_whitespace(alk->redirection);
	if (alk->redirection[0] != '\0')
		open_file(alk, fd);
	return (0);
}

int		find_fd(t_parsing *alk, char **env)
{
	t_fd fd = (t_fd){ 0 };
	t_parsing *tmp;

	tmp = alk;
	fd.in = 0;
	fd.out = 1;
	ft_check_env(alk);
	if (alk->next)
		ft_pipe(alk, &fd, env);
	else
	{
		if (open_file(alk, &fd) == -1)
			return (0);
		builtin_exec_simple(alk, &fd, env);
	}
	alk = tmp;
	return (0);
}
