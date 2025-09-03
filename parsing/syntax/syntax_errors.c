/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:01:00 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:56:37 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	check_first_token(t_token *curr)
{
	if (curr->type == PIPE)
	{
		if (curr->next && curr->next->type == PIPE)
			return (print_syntax(
					"syntax error near unexpected token", DOUBLE_PIPE));
		return (print_syntax(
				"syntax error near unexpected token", curr->type));
	}
	return (0);
}

static int	check_pipe_errors(t_token *curr)
{
	if (!curr->next)
		return (print_syntax(
				"syntax error near unexpected token `newline'", -1));
	if (curr->next->type == PIPE)
		return (print_syntax(
				"syntax error near unexpected token", DOUBLE_PIPE));
	return (0);
}

static int	check_redirection_errors(t_token *curr)
{
	if (!curr->next)
		return (print_syntax(
				"syntax error near unexpected token `newline'", -1));
	if (curr->next->type != WORD)
	{
		if (curr->next->type == PIPE)
			return (print_syntax(
					"syntax error near unexpected token `newline'", -1));
		return (print_syntax(
				"syntax error near unexpected token", curr->next->type));
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (!curr)
		return (0);
	if (check_first_token(curr))
		return (258);
	while (curr)
	{
		if (contains_unclosed_quote(curr->value))
			return (print_syntax("syntax error: unclosed quote", -1));
		if (curr->type == PIPE && check_pipe_errors(curr))
			return (258);
		if ((curr->type == RED_IN || curr->type == RED_OUT
				|| curr->type == APPEND || curr->type == HEREDOC)
			&& check_redirection_errors(curr))
			return (258);
		curr = curr->next;
	}
	return (0);
}
