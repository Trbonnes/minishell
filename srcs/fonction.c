/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:55:04 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/21 18:28:00 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_echo(t_parsing *alk, t_fd *fd)
{
	int len;

	if (fd->out == -1)
		return (-1);
	printf("%d\n", fd->out);
	len = ft_strlen(alk->param);
	write(fd->out, alk->param, len);
	if (alk->echo_option == FALSE)
		write(fd->out, "\n", 1);
	return (0);
}

int		ft_cd(t_parsing *alk)
{
	int		ret;

	if (!alk->param)
		return (-1);
	alk->param = ft_whitespace(alk->param);
	// if (str[0] == '.' && str[1] == '.')
		// ft_up_directory();
	if (alk->param[0] == '\0' || alk->param[0] == '~')
		ft_home(alk);
	ret = chdir(alk->param);
	return (ret);
}

int		ft_pwd(t_fd *fd)
{
	char	*buf;
	int		len;

	if (fd->out == -1)
		return (-1);
	if (!(buf = malloc(sizeof(char) * 1024)))
		return (-1);
	getcwd(buf, 1024);
	len = ft_strlen(buf);
	write(fd->out, buf, len);
	free(buf);
	return (0);
}

void	ft_exit(void)
{
	write(1, "exit", 4);
	exit(1);
}

// int		main(void)
// {
// 	t_parsing alk;

// 	// int fd;
// 	// char *str;
// 	// str = ft_strdup("../../..");
// 	// ft_exit();
// 	// fd = open("caca", O_WRONLY | O_CREAT, S_IRWXU);
// 	// ft_echo("Coucou fils", fd, FALSE);
// 	// ft_cd(str);
// 	// fd = open("docker.sh", O_RDONLY);
// 	// printf("%d\n", fd);
// 	// ft_pwd(1);

// 	// alk.builtin_detected = 1;
// 	// alk.echo_option = 0;
// 	// alk.param = ft_strdup("a");
// 	// alk.redirection = ft_strdup("> b< c< d> e");
// 	find_fd(&alk);
// 	return (0);
// }
