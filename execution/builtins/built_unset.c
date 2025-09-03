#include "../.././parsing/main.h"

void	remove_env_node(t_env *cur, t_env *env_list)
{
	t_env	*prev;

	prev = env_list;
	if (cur == env_list)
	{
		env_list = cur->next;
		free_list_node(cur);
		return ;
	}
	while (prev && prev->next != cur)
		prev = prev->next;
	if (prev)
	{
		prev->next = cur->next;
		free_list_node(cur);
	}
}

int	ft_unset(char **command, t_env *env_list)
{
	int		j;
	t_env	*cur;

	j = 1;
	while (command[j])
	{
		cur = env_list;
		while (cur)
		{
			if (!ft_check_strcmp(command[j], cur->key))
				remove_env_node(cur, env_list);
			cur = cur->next;
		}
		j++;
	}
	return (0);
}
