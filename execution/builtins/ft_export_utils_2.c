#include "../.././parsing/main.h"

void	desplay_list_export(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->eg == true)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	swap_nodes(t_env *node1, t_env *node2)
{
	char	*temp_key;
	char	*temp_value;
	bool	temp_eg;

	if (!node1 || !node2)
		return ;
	temp_key = node1->key;
	node1->key = node2->key;
	node2->key = temp_key;
	temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;
	temp_eg = node1->eg;
	node1->eg = node2->eg;
	node2->eg = temp_eg;
}
