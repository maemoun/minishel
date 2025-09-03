/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_all_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:13:58 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 00:51:39 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static t_command	*init_command(t_command	*prev, t_data	*data)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->data = data;
	cmd->command = NULL;
	cmd->next_command = NULL;
	cmd->prev = prev;
	cmd->red = NULL;
	cmd->fd_pipe[0] = -1;
	cmd->fd_pipe[1] = -1;
	cmd->fd_herdoc[0] = -1;
	cmd->fd_herdoc[1] = -1;
	cmd->fd_cmd[0] = -1;
	cmd->fd_cmd[1] = -1;
	cmd->cmd_backup[0] = -1;
	cmd->cmd_backup[1] = -1;
	return (cmd);
}

static void	append_command(t_command **head, t_command **last,
								t_command *new_cmd)
{
	if (!*head)
		*head = new_cmd;
	else
		(*last)->next_command = new_cmd;
	*last = new_cmd;
}

static void	skip_to_next_pipe(t_token **tokens)
{
	while (*tokens && (*tokens)->type != PIPE)
		*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
}

t_command	*extract_all_commands(t_token *tokens, t_env *env, t_data *data)
{
	t_command	*head;
	t_command	*last;
	t_command	*new_cmd;
	t_token		*scan;

	head = NULL;
	last = NULL;
	while (tokens)
	{
		new_cmd = init_command(last, data);
		if (!new_cmd)
			return (NULL);
		scan = tokens;
		new_cmd->command = get_command_args(&tokens);
		new_cmd->red = get_redirections(&scan, env, data);
		append_command(&head, &last, new_cmd);
		skip_to_next_pipe(&tokens);
	}
	return (head);
}
