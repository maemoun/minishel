/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:11:21 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 15:00:48 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static char	handle_dollar_quote(const char *str, int *i)
{
	if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '"'))
	{
		*i += 2;
		return (str[*i - 1]);
	}
	return (0);
}

static void	process_char(const char *str, char *res, int *i, int *j)
{
	static char	quote = 0;

	if (!quote && (str[*i] == '\'' || str[*i] == '"'))
		quote = str[*i];
	else if (quote && str[*i] == quote)
		quote = 0;
	else
		res[(*j)++] = str[*i];
	(*i)++;
}

char	*remove_quotes(const char *str)
{
	int		i;
	int		j;
	int		len;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	quote = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!quote)
			quote = handle_dollar_quote(str, &i);
		process_char(str, res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}
