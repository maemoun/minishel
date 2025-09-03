/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:01:43 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 00:44:03 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	handle_dollar_quote(char *s, int i)
{
	char	quote;

	quote = s[i + 1];
	i += 2;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static int	handle_redirection(char *s, int i)
{
	if (s[i + 1] == s[i])
		return (i + 2);
	return (i + 1);
}

static int	handle_normal_quotes(char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

int	get_token_end(char *s, int i)
{
	if (s[i] == '$' && (s[i + 1] == '\'' || s[i + 1] == '"'))
		return (handle_dollar_quote(s, i));
	if (s[i] == '<' || s[i] == '>')
		return (handle_redirection(s, i));
	if (s[i] == '|')
		return (i + 1);
	if (s[i] == '"' || s[i] == '\'')
		return (handle_normal_quotes(s, i));
	while (s[i] && !ft_isspace(s[i]) && s[i] != '"' && s[i] != '\''
		&& s[i] != '<' && s[i] != '>' && s[i] != '|')
		i++;
	return (i);
}
