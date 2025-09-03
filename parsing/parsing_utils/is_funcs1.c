/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_funcs1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:10:00 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:41:38 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	is_quoted(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')));
}

int	has_quote(const char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

int	is_single_quoted(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}

int	is_operator(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "|") == 0)
		return (1);
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, "<") == 0)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
