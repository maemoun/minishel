/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:52:41 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:09:22 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	free_redirections(t_redirection *head)
{
	t_redirection	*tmp;

	while (head)
	{
		tmp = head->next_red;
		free(head->name);
		free(head);
		head = tmp;
	}
}

static t_redirection	*process_redirection_token(
	t_token *red_token, t_env *env, t_data *data)
{
	t_token			*file_token;
	t_redirection	*new_red;

	file_token = red_token->next;
	if (!file_token)
		return (NULL);
	new_red = create_redirection(red_token, file_token, env, data);
	return (new_red);
}

t_redirection	*get_redirections(t_token **tokens, t_env *env, t_data *data)
{
	t_redirection	*head;
	t_redirection	*last;
	t_redirection	*new_red;
	t_token			*tmp;

	head = NULL;
	last = NULL;
	tmp = *tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == RED_IN || tmp->type == RED_OUT
			|| tmp->type == HEREDOC || tmp->type == APPEND)
		{
			new_red = process_redirection_token(tmp, env, data);
			if (!new_red)
				return (free_redirections(head), NULL);
			append_redirection(&head, &last, new_red);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	return (head);
}
