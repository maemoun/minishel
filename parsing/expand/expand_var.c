/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:53:14 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 00:28:24 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (!strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_exit_status(char *res, t_data *dt)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(dt->exit_status);
	if (!status)
	{
		free(res);
		return (NULL);
	}
	tmp = append_str(res, status);
	free(status);
	return (tmp);
}

static char	*expand_key(t_exp *ex, t_env *env)
{
	char	*key;
	char	*val;
	char	*tmp;
	int		j;

	ex->start = ex->i;
	while (is_var_char(ex->src[ex->i]))
		ex->i++;
	ex->len = ex->i - ex->start;
	key = malloc(ex->len + 1);
	if (!key)
		return (free(ex->res), NULL);
	j = 0;
	while (j < ex->len)
	{
		key[j] = ex->src[ex->start + j];
		j++;
	}
	key[ex->len] = '\0';
	val = get_env_value(env, key);
	tmp = append_str(ex->res, val);
	free(key);
	return (tmp);
}

static void	handle_dollar(t_exp *ex, t_data *dt, t_env *env)
{
	ex->i++;
	if (ex->src[ex->i] == '?')
		ex->res = expand_exit_status(ex->res, dt);
	else if (is_var_char(ex->src[ex->i]))
		ex->res = expand_key(ex, env);
	else
		ex->i++;
}

char	*expand_var(const char *src, t_data *dt, t_env *env)
{
	t_exp	ex;

	ex.src = src;
	ex.res = malloc(1);
	if (!ex.res)
		return (NULL);
	ex.res[0] = '\0';
	ex.i = 0;
	while (ex.src[ex.i])
	{
		if (ex.src[ex.i] == 1)
			ex.res = append_char(ex.res, '$');
		else if (ex.src[ex.i] == '$')
			handle_dollar(&ex, dt, env);
		else
			ex.res = append_char(ex.res, ex.src[ex.i]);
		if (!ex.res)
			return (NULL);
		ex.i++;
	}
	return (ex.res);
}
