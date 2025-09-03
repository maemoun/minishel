/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:08:56 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 00:52:09 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	handle_escaped_dollar(const char *input, t_fir_expand_elements *st)
{
	(void)input;
	st->result = ft_strjoin(st->result, "\\");
	st->result = ft_strjoin(st->result, "$");
	st->i += 2;
}

void	handle_quotes(const char *input, t_fir_expand_elements *st)
{
	st->result = expand_quote_state(input, st);
}

void	handle_variable(const char *input, t_fir_expand_elements *st)
{
	if (input[st->i + 1] == '?')
	{
		st->result = f_expand_exit_status(st);
		st->i += 2;
	}
	else if (ft_is_valid_var_char(input[st->i + 1]))
		st->result = expand_variable_name(input, st);
	else
	{
		st->result = ft_strjoin(st->result, "$");
		st->i++;
	}
}

void	handle_plain_char(const char *input, t_fir_expand_elements *st)
{
	st->result = expand_char_literal(st, input[st->i]);
	st->i++;
}

char	*first_expand_variable(const char *input, t_env *env,
		int last_exit_status)
{
	t_fir_expand_elements	st;

	st.env = env;
	st.last_exit_status = last_exit_status;
	st.i = 0;
	st.in_single = 0;
	st.in_double = 0;
	st.result = ft_strndup("", 0);
	while (input[st.i])
	{
		if (input[st.i] == '\\' && input[st.i + 1] == '$' && !st.in_single)
			handle_escaped_dollar(input, &st);
		else if ((input[st.i] == '\'' && !st.in_double)
			|| (input[st.i] == '"' && !st.in_single))
			handle_quotes(input, &st);
		else if (input[st.i] == '$' && !st.in_single)
			handle_variable(input, &st);
		else
			handle_plain_char(input, &st);
	}
	return (st.result);
}
