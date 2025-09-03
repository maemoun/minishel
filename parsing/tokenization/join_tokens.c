/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:39:11 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:00:43 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	is_empty_quote(const char *s)
{
	return ((s[0] == '\'' && s[1] == '\'' && s[2] == '\0')
		|| (s[0] == '"' && s[1] == '"' && s[2] == '\0'));
}

static void	join_empty_quote(t_token *curr)
{
	t_token	*tmp;

	tmp = curr->next;
	curr->has_space_after = tmp->has_space_after;
	curr->next = tmp->next;
	free(tmp->value);
	free(tmp);
}

static void	concat_two_tokens(t_token *curr)
{
	t_token	*tmp;
	char	*joined;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(curr->value);
	l2 = ft_strlen(curr->next->value);
	joined = malloc(l1 + l2 + 1);
	if (!joined)
		return ;
	my_strcpy(joined, curr->value);
	my_strcat(joined, curr->next->value);
	free(curr->value);
	curr->value = joined;
	tmp = curr->next;
	curr->has_space_after = tmp->has_space_after;
	curr->next = tmp->next;
	free(tmp->value);
	free(tmp);
}

static void	join_two_tokens(t_token *curr)
{
	if (is_empty_quote(curr->next->value))
		join_empty_quote(curr);
	else
		concat_two_tokens(curr);
}

void	join_tokens_with_no_space(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr && curr->next)
	{
		if (curr->has_space_after == 0)
			join_two_tokens(curr);
		else
			curr = curr->next;
	}
	clean_all_tokens(*tokens);
}
