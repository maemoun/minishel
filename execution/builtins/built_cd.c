#include "../.././parsing/main.h"

char	*get_value(t_env *env_list, char *key)
{
	t_env	*tmp;

	if (!env_list || !key)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		if (!ft_check_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_env(char *key, char *value, t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (!ft_check_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup_2(value);
			tmp->eg = true;
			return ;
		}
		tmp = tmp->next;
	}
	list_add_back(env_list, list_new_node(value, key, true));
}

char	*resolve_cd_path(char *str, t_env *env_list)
{
	char	*ret;

	if (!str || ft_check_strcmp(str, "--") == 0
		|| ft_check_strcmp(str, "~") == 0)
	{
		ret = get_value(env_list, "HOME");
		if (!ret)
			return (ft_putstr_fd2("cd: HOME not set\n", 2), NULL);
		return (ret);
	}
	else if (!ft_check_strcmp(str, "-"))
	{
		ret = get_value(env_list, "OLDPWD");
		if (!ret || !*ret)
			return (ft_putstr_fd2("cd: OLDPWD not set\n", 2), NULL);
		return (ret);
	}
	else if (!ft_strncmp_2(str, "~/", 2))
	{
		ret = ft_strjoin_2(get_value(env_list, "HOME"), str + 1);
		return (ret);
	}
	else
		return (str);
}

int	ft_cd(t_env *env_list, char *path)
{
	char	*oldpwd;
	char	*p;

	p = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (print_error(errno, p, "cd"), 1);
	p = resolve_cd_path(path, env_list);
	if (!p)
		return (free(oldpwd), 1);
	if (chdir(p) == -1)
		return (free(oldpwd), print_error(errno, p, "cd"), 1);
	if (!ft_strncmp_2(path, "~/", 2))
		free(p);
	p = getcwd(NULL, 0);
	if (!p)
		return (free(oldpwd), print_error(errno, p, "cd"), 1);
	update_env("PWD", p, &env_list);
	update_env("OLDPWD", oldpwd, &env_list);
	if (!ft_check_strcmp(path, "-"))
		printf("%s\n", p);
	free(p);
	free(oldpwd);
	return (0);
}
