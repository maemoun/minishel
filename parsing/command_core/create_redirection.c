/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:06:36 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:09:12 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	append_redirection(t_redirection	**head, t_redirection	**last,
		t_redirection	*new_red)
{
	if (!*head)
		*head = new_red;
	else
		(*last)->next_red = new_red;
	*last = new_red;
}

static void	set_red_type(t_redirection *red, t_token *red_token)
{
	if (red_token->type == RED_IN)
		red->type = INPUT;
	else if (red_token->type == RED_OUT)
		red->type = OUTPUT;
	else if (red_token->type == HEREDOC)
		red->type = RED_HEREDOC;
	else
		red->type = RED_APPEND;
}

static void	set_red_name(t_redirection *red, t_token *file_token, t_env *env)
{
	char	*key;
	char	*val;

	if (file_token->value[0] == '$' && red->type != RED_HEREDOC)
	{
		key = file_token->value + 1;
		val = first_get_env_value(key, env);
		red->name = ft_strdup(val);
		if (!red->name)
			red->name = ft_strdup("");
	}
	else
		red->name = ft_strdup(file_token->value);
}

t_redirection	*create_redirection(t_token *red_token, t_token *file_token,
					t_env *env, t_data *data)
{
	t_redirection	*new_red;

	(void)data;
	new_red = malloc(sizeof(t_redirection));
	if (!new_red)
		return (NULL);
	set_red_type(new_red, red_token);
	set_red_name(new_red, file_token, env);
	if (!new_red->name)
	{
		free(new_red);
		return (NULL);
	}
	new_red->next_red = NULL;
	if (new_red->type == RED_HEREDOC)
		new_red->expand_variable = !file_token->has_quote;
	return (new_red);
}
