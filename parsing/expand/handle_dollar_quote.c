/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:42:26 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:53:28 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*extract_dollar_quote(const char *str)
{
	char	quote;
	int		i;
	int		len;
	char	*res;
	int		j;

	quote = str[1];
	i = 2;
	len = 0;
	while (str[i + len] && str[i + len] != quote)
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len)
	{
		res[j] = str[i + j];
		j++;
	}
	res[len] = '\0';
	return (res);
}

char	*t_handle_dollar_quote(const char *str)
{
	if (str[0] == '$' && (str[1] == '\'' || str[1] == '"'))
		return (extract_dollar_quote(str));
	return (NULL);
}
