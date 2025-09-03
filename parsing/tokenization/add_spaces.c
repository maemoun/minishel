/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:33:43 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 00:42:49 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	should_add_space_after(char c)
{
	return (c != '\0' && c != ' ');
}

static void	ft_handle_quotes(char *input, t_parse_state *ps)
{
	if (!ps->in_quote && is_quote(input[ps->i]))
	{
		ps->in_quote = 1;
		ps->quote_char = input[ps->i];
		ps->new_str[ps->j++] = input[ps->i++];
	}
	else if (ps->in_quote && input[ps->i] == ps->quote_char)
	{
		ps->in_quote = 0;
		ps->new_str[ps->j++] = input[ps->i++];
	}
}

static void	handle_symbols(char *input, t_parse_state *ps)
{
	if (is_should_add_space_before(ps->new_str, ps->j))
		ps->new_str[ps->j++] = ' ';
	ps->new_str[ps->j++] = input[ps->i];
	if ((input[ps->i] == '<' || input[ps->i] == '>')
		&& input[ps->i] == input[ps->i + 1])
		ps->new_str[ps->j++] = input[ps->i++];
	ps->i++;
	if (should_add_space_after(input[ps->i]))
		ps->new_str[ps->j++] = ' ';
}

static void	handle_normal(char *input, t_parse_state *ps)
{
	if (!ps->in_quote && !is_symbol(input[ps->i]))
		ps->new_str[ps->j++] = input[ps->i++];
	else if (ps->in_quote)
		ps->new_str[ps->j++] = input[ps->i++];
}

char	*add_spaces_around_symbols(char *input)
{
	t_parse_state	ps;

	ps.i = 0;
	ps.j = 0;
	ps.in_quote = 0;
	ps.quote_char = 0;
	ps.new_str = malloc(ft_strlen(input) * 3 + 1);
	if (!ps.new_str)
		return (NULL);
	while (input[ps.i])
	{
		if (!ps.in_quote && is_quote(input[ps.i]))
		{
			ft_handle_quotes(input, &ps);
			continue ;
		}
		if (!ps.in_quote && is_symbol(input[ps.i]))
		{
			handle_symbols(input, &ps);
			continue ;
		}
		handle_normal(input, &ps);
	}
	ps.new_str[ps.j] = '\0';
	return (ps.new_str);
}
