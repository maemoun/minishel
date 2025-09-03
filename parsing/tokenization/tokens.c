/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:30:38 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:03:18 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_token	*new_token(char *value, int has_space_after)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->has_space_after = has_space_after;
	node->has_quote = has_quote(value);
	node->next = NULL;
	return (node);
}

void	append_token(t_token **head, t_token *new_node)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	add_word_token(char *s, int *i, t_token **tokens)
{
	int		start;
	int		end;
	int		len;
	char	*val;
	int		has_space;

	start = *i;
	end = get_token_end(s, *i);
	len = end - start;
	val = ft_substr(s, start, len);
	if (!val)
		return ;
	*i = end;
	has_space = ft_isspace(s[*i]);
	append_token(tokens, new_token(val, has_space));
}

t_token	*tokenize(char *s)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		add_word_token(s, &i, &tokens);
	}
	return (tokens);
}

void	assign_token_types(t_token *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->value, "|") == 0)
			tokens->type = PIPE;
		else if (ft_strcmp(tokens->value, "<") == 0)
			tokens->type = RED_IN;
		else if (ft_strcmp(tokens->value, ">") == 0)
			tokens->type = RED_OUT;
		else if (ft_strcmp(tokens->value, "<<") == 0)
			tokens->type = HEREDOC;
		else if (ft_strcmp(tokens->value, ">>") == 0)
			tokens->type = APPEND;
		else
			tokens->type = WORD;
		tokens = tokens->next;
	}
}
