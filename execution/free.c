#include ".././parsing/main.h"

void	free_list_node(t_env *node)
{
	if (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		free(node);
	}
	node = NULL;
}

void	free_list(t_env **env_list)
{
	t_env	*cur;
	t_env	*next;

	if (!env_list || !*env_list)
		return ;
	cur = *env_list;
	while (cur)
	{
		next = cur->next;
		free_list_node(cur);
		cur = next;
	}
	*env_list = NULL;
}

void	free_redirec_list(t_redirection *red)
{
	t_redirection	*temp;

	while (red)
	{
		temp = red;
		red = red->next_red;
		free(temp->name);
		free(temp);
	}
}

void	free_cmd_node(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->command && cmd->command[i])
		free(cmd->command[i++]);
	if (cmd->command)
		free(cmd->command);
	if (cmd->red)
		free_redirec_list(cmd->red);
	free(cmd);
}

void	free_cmd_list(t_command *cmd)
{
	t_command	*next;

	while (cmd)
	{
		next = cmd->next_command;
		free_cmd_node(cmd);
		cmd = next;
	}
}
