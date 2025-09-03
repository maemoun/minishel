/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_funcs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:38:11 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:41:41 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

int	ft_is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_should_add_space_before(char *str, int pos)
{
	return (pos > 0 && str[pos - 1] != ' ');
}
