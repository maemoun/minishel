#include "../.././parsing/main.h"

void	sort_export(t_env *env_list)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*small;

	new = NULL;
	new = ft_copy_env(env_list);
	tmp = new;
	while (tmp)
	{
		small = tmp;
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_check_strcmp(tmp2->key, small->key) < 0)
				small = tmp2;
			tmp2 = tmp2->next;
		}
		if (small != tmp)
			swap_nodes(small, tmp);
		tmp = tmp->next;
	}
	desplay_list_export(new);
	free_list(&new);
}

char	*parss_value(char *command, bool *eg)
{
	int		i;
	char	*value;

	i = 0;
	while (command[i] && command[i] != '=')
		i++;
	if (command[i] == '=')
	{
		value = ft_strdup_2(command + i + 1);
		*eg = true;
	}
	else
		value = ft_strdup_2(command + i);
	return (value);
}

int	export_new(char *command, t_command *cmd, t_env *env_list)
{
	bool	eg;
	char	*value;
	char	*key;

	eg = false;
	value = parss_value(command, &eg);
	key = get_valide_key(command);
	if (!key)
	{
		free(value);
		ft_putstr_fd2("minishell: export: `", 2);
		ft_putstr_fd2(command, 2);
		ft_putstr_fd2("': not a valid identifier\n", 2);
		return (1);
	}
	add_export_list(env_list, value, key, eg);
	if (value)
		free(value);
	if (key)
		free(key);
	return (0);
}

int	ft_export(char **command, t_command *cmd, t_env *env_list)
{
	int	j;
	int	ret;

	j = 1;
	ret = 0;
	if (!command[j])
	{
		sort_export(env_list);
		return (0);
	}
	while (command[j])
	{
		if (export_new(command[j], cmd, env_list))
			ret = 1;
		j++;
	}
	return (ret);
}
