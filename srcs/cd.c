/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trdella- <trdella-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:54:45 by trdella-          #+#    #+#             */
/*   Updated: 2020/01/22 12:06:22 by trdella-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

int		ft_up_directory(t_parsing *alk)
{
	char *buf;
	int i;
	int j;

	j = 0;
	i = 0;
	if (!(buf = malloc(sizeof(char) * 1024)))
		return (-1);
	getcwd(buf, 1024);
	while (buf[i])
		i++;	
	if (i > 0)
		i--;
	if (buf[i] == '/' && i > 0)
		i--;
	while (buf[i] != '/' && i > 0)
		i--;
	if (i == 0)
		alk->param = ft_substr(buf, 0, 1);
	else
		alk->param = ft_substr(buf, 0, i);
	free(buf);
	return (0);
}

void	ft_home(t_parsing *alk)
{
	const char users[17] = "/Users/trdella-/";

	if (alk->param[0] == '~')
		alk->param = ft_strjoin(users, alk->param + 2);
	else
		alk->param = ft_strdup(users);
}

// int main(void)
// {
// 	t_parsing alk;

// 	alk.builtin_detected = 1;
// 	alk.echo_option = 0;
// 	alk.param = ft_strdup("..");
// 	alk.redirection = ft_strdup("");
// 	ft_cd(&alk);

// 	return (0);
// }