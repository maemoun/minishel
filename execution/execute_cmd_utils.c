#include ".././parsing/main.h"

int	list_size(t_env *env_list)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	*prepare_env_value(t_env *tmp)
{
	char	*join;
	char	*result;

	if (ft_check_strcmp(tmp->key, "SHLVL") == 0)
	{
		tmp->shlvl++;
		free(tmp->value);
		tmp->value = ft_itoa(tmp->shlvl);
	}
	if (tmp->eg)
		join = ft_strjoin_2(tmp->key, "=");
	else
		join = ft_strdup_2(tmp->key);
	result = ft_strjoin_2(join, tmp->value);
	if (join)
		free(join);
	return (result);
}

char	**build_environment_array(t_env *env_list)
{
	int		len;
	t_env	*tmp;
	int		i;
	char	**env;

	i = 0;
	len = list_size(env_list);
	tmp = env_list;
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
	{
		print_error(errno, NULL, NULL);
		return (NULL);
	}
	while (tmp)
	{
		env[i++] = prepare_env_value(tmp);
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
