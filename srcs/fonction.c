/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:04 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/17 18:57:32 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_echo(char *str, int fd, int bool)
{
	int len;
	
	if (fd == -1)
		return (-1);
	len = ft_strlen(str);
	write(fd, str, len);
	if (bool == FALSE)
		write(fd, "\n", 1);
	return (0);
}

int		ft_cd(char *str)
{
	char *copy;
	int ret;
	
	if (!str)
		return (-1);
	copy = ft_whitespace(str);
	if (copy[0] == '\0' || copy[0] == '~')
		copy = ft_home(copy);
	ret = chdir(copy);
	free(copy);
	return (ret);
}

int		ft_pwd(int fd)
{
	char *buf;
	int len;
	
	if (fd == -1)
		return (-1);
	if (!(buf = malloc(sizeof(char) * 1024)))
		return (-1);
	getcwd(buf, 1024);
	len = ft_strlen(buf);
	write(fd, buf, len);
	free(buf);
	return (0);
}



int main(void)
{
	// int fd;
	// char *str;
	
	
	// fd = open("caca", O_WRONLY | O_CREAT, S_IRWXU);
	// ft_echo("Coucou fils", fd, FALSE);
	ft_cd("../../..");
	// fd = open("docker.sh", O_RDONLY);
	// printf("%d\n", fd);
	ft_pwd(1);
	return (0);
}