/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:11:20 by abdo              #+#    #+#             */
/*   Updated: 2025/08/21 14:51:07 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*first_get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key))
			&& ft_strlen(env->key) == ft_strlen(key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*f_expand_exit_status(t_fir_expand_elements *st)
{
	char	*status_str;
	char	*new_result;

	status_str = ft_itoa(st->last_exit_status);
	new_result = ft_strjoin(st->result, status_str);
	free(status_str);
	return (new_result);
}

char	*expand_variable_name(const char *input, t_fir_expand_elements *st)
{
	size_t	start;
	char	*var_name;
	char	*val;

	st->i++;
	start = st->i;
	while (ft_is_valid_var_char(input[st->i]))
		st->i++;
	var_name = ft_strndup(&input[start], st->i - start);
	val = first_get_env_value(var_name, st->env);
	if (val)
		st->result = ft_strjoin(st->result, val);
	else
	{
		st->result = ft_strjoin(st->result, "$");
		st->result = ft_strjoin(st->result, var_name);
	}
	free(var_name);
	return (st->result);
}

char	*expand_quote_state(const char *input, t_fir_expand_elements *st)
{
	if (input[st->i] == '\'' && !st->in_double)
	{
		st->in_single = !st->in_single;
		st->result = ft_strjoin(st->result, "'");
		st->i++;
	}
	else if (input[st->i] == '"' && !st->in_single)
	{
		st->in_double = !st->in_double;
		st->result = ft_strjoin(st->result, "\"");
		st->i++;
	}
	return (st->result);
}

char	*expand_char_literal(t_fir_expand_elements *st, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = 0;
	return (ft_strjoin(st->result, temp));
}
