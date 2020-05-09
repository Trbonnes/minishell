/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trostan <trostan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:28:13 by trbonnes          #+#    #+#             */
/*   Updated: 2020/05/09 12:15:20 by trostan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fonction.h"

extern int		g_last_return_value;
extern t_env	*g_env_list;

void	sort_list(t_env **sorted)
{
	t_env	*count;
	t_env	*current;
	char	*key;
	char	*ref;

	count = *sorted;
	while (count)
	{
		current = *sorted;
		while (current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				key = current->key;
				ref = current->ref;
				current->key = current->next->key;
				current->ref = current->next->ref;
				current->next->key = key;
				current->next->ref = ref;
			}
			else
				current = current->next;
		}
		count = count->next;
	}
}

void	ft_export_loop(t_fd *fd, t_env *lst)
{
	int		len;

	len = 0;
	if (lst->ref[0] != '\0')
	{
		while (lst->ref[len] != '=')
			len++;
		len++;
		write(fd->out, "declare -x ", 11);
		write(fd->out, lst->key, len - 1);
		write(fd->out, "=\"", 2);
		write(fd->out, lst->ref + len, ft_strlen(lst->ref) - len);
		write(fd->out, "\"\n", 2);
	}
}

int		last_return_setup(int status)
{
	int last_return_value;

	last_return_value = status;
	if (status == 2)
		last_return_value = 130;
	else if (status == 3)
		last_return_value = 131;
	else if (status == 32512)
		last_return_value = 127;
	else if (status == 65280)
		last_return_value = 255;
	else if (status == 512)
		last_return_value = 2;
	else if (status == 256)
		last_return_value = 1;
	else if (status == 33280)
		last_return_value = 1;
	return (last_return_value);
}

int		chevron_error(void)
{
	write(2,
	"minishell: syntax error near unexpected token `newline'\n", 56);
	g_last_return_value = 2;
	return (-1);
}

int		ft_ref_len(t_env *search)
{
	int		j;
	int		k;

	j = 0;
	k = 1;
	while (search->ref[k - 1] != '=')
		k++;
	while (search->ref[k + j])
		j++;
	return (j);
}
