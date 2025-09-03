/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:30:41 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 16:12:04 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_tokens(t_token *list)
{
	t_token	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}

void	free_redirections(t_redirection *red)
{
	t_redirection	*r_tmp;

	while (red)
	{
		r_tmp = red->next_red;
		free(red->name);
		free(red);
		red = r_tmp;
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next_command;
		if (cmd->command)
		{
			i = 0;
			while (cmd->command[i])
				free(cmd->command[i++]);
			free(cmd->command);
		}
		free_redirections(cmd->red);
		free(cmd);
		cmd = tmp;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	clean_all_tokens(t_token *curr)
{
	char	*clean;

	while (curr)
	{
		clean = remove_quotes(curr->value);
		free(curr->value);
		curr->value = clean;
		curr = curr->next;
	}
}
