/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_delimiters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:00:25 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:00:45 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	mark_heredoc_delimiters(t_token **tokens)
{
	t_token	*curr;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr)
	{
		if (curr->next && !curr->has_space_after
			&& has_quote(curr->next->value))
			curr->has_quote = 1;
		curr = curr->next;
	}
}
