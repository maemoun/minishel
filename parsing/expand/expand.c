/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:53:14 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:51:05 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static char	*copy_escapes(const char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			new_str[j++] = 1;
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*preprocess_escapes(const char *str)
{
	return (copy_escapes(str));
}

static void	expand_single_token(t_token *curr, t_data *dt, t_env *env)
{
	char	*tmp;
	char	*clean;
	char	*expanded;

	tmp = t_handle_dollar_quote(curr->value);
	if (tmp)
	{
		free(curr->value);
		curr->value = tmp;
	}
	else
	{
		clean = preprocess_escapes(curr->value);
		expanded = expand_var(clean, dt, env);
		free(clean);
		free(curr->value);
		curr->value = expanded;
	}
}

void	expand_tokens(t_token **tokens, t_data *dt, t_env *env)
{
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (prev && prev->type == HEREDOC)
		{
			prev = curr;
			curr = curr->next;
			continue ;
		}
		if (!is_single_quoted(curr->value))
			expand_single_token(curr, dt, env);
		prev = curr;
		curr = curr->next;
	}
}
