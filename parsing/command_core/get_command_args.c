/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:16:46 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:09:18 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	skip_redirection(t_token **tokens)
{
	if (*tokens && ((*tokens)->type == RED_IN
			|| (*tokens)->type == RED_OUT
			|| (*tokens)->type == HEREDOC
			|| (*tokens)->type == APPEND))
	{
		*tokens = (*tokens)->next;
		if (*tokens)
			*tokens = (*tokens)->next;
	}
}

static void	add_word_arg(char **args, int *i, t_token **tokens)
{
	args[*i] = ft_strdup((*tokens)->value);
	(*i)++;
	*tokens = (*tokens)->next;
}

char	**get_command_args(t_token **tokens)
{
	int		args_count;
	char	**args;
	int		i;

	args_count = count_args(*tokens);
	args = malloc(sizeof(char *) * (args_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
			add_word_arg(args, &i, tokens);
		else
			skip_redirection(tokens);
	}
	args[i] = NULL;
	return (args);
}
