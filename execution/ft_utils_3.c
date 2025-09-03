#include ".././parsing/main.h"

void	list_add_back(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	if (!(*env_list))
	{
		(*env_list) = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*list_new_node(char *value, char *key, bool eg)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (print_error(errno, NULL, NULL), NULL);
	new->key = ft_strdup_2(key);
	new->value = ft_strdup_2(value);
	new->eg = eg;
	new->next = NULL;
	return (new);
}

void	p2char(char ***ptr)
{
	int	r;

	if (!ptr || !*ptr)
		return ;
	r = 0;
	while ((*ptr)[r])
		free((*ptr)[r++]);
	free(*ptr);
	*ptr = NULL;
}

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}
