#include "../includes/fonction.h"

extern t_env *g_env_list;

t_env	*lst_cpy(t_env *lst)
{
	t_env	*save;
	t_env	*tmp;

	if (!(lst = malloc(sizeof(t_env))))
		return (NULL);
	tmp = lst;
	save = g_env_list;
	while (g_env_list)
	{
		lst->key = ft_strdup(g_env_list->key);
		lst->ref = ft_strdup(g_env_list->ref);
		if (g_env_list->next)
		{
			if (!(lst->next = malloc(sizeof(t_env))))
				return (NULL);
			lst = lst->next;
		}
		else
			lst->next = NULL;
		g_env_list = g_env_list->next;
	}
	g_env_list = save;
	lst = tmp;
	return (lst);
}
