#include ".././parsing/main.h"

static char	*expand_with_braces(const char *input, t_fir_expand_elements *st)
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
	free(var_name);
	if (input[st->i] == '}')
		st->i++;
	return (st->result);
}

static char	*expand_without_braces(const char *input, t_fir_expand_elements *st)
{
	size_t	start;
	char	*var_name;
	char	*val;

	start = st->i;
	while (ft_is_valid_var_char(input[st->i]))
		st->i++;
	var_name = ft_strndup(&input[start], st->i - start);
	val = first_get_env_value(var_name, st->env);
	if (val)
		st->result = ft_strjoin(st->result, val);
	free(var_name);
	return (st->result);
}

char	*expand_variable_name_herdoc(const char *input,
				t_fir_expand_elements *st)
{
	st->i++;
	if (input[st->i] == '{')
		return (expand_with_braces(input, st));
	return (expand_without_braces(input, st));
}

static void	handle_variable_herdoc(const char *input, t_fir_expand_elements *st)
{
	if (input[st->i + 1] == '?')
	{
		st->result = f_expand_exit_status(st);
		st->i += 2;
	}
	else if (ft_is_valid_var_char(input[st->i + 1]) || input[st->i + 1] == '{')
		expand_variable_name_herdoc(input, st);
	else
	{
		st->result = ft_strjoin(st->result, "$");
		st->i++;
	}
}

char	*expand_var_herdoc(const char *input, t_env *env, int last_exit_status)
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
			handle_variable_herdoc(input, &st);
		else
			handle_plain_char(input, &st);
	}
	return (st.result);
}
