#include ".././parsing/main.h"

bool	check_if_is_a_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

char	**get_system_paths(t_env *env_list)
{
	char	*value;

	value = get_value(env_list, "PATH");
	if (!value)
		return (NULL);
	return (ft_split(value, ':'));
}

static char	*search_in_path(char **path, char *command)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		join = ft_strjoin_2("/", command);
		tmp = ft_strdup_2(join);
		free(join);
		join = ft_strjoin_2(path[i], tmp);
		free(tmp);
		if (access(join, X_OK) == 0)
			return (join);
		free(join);
		i++;
	}
	return (NULL);
}

static void	print_command_not_found(char *command)
{
	ft_putstr_fd2("minishell: ", 2);
	ft_putstr_fd2(command, 2);
	ft_putstr_fd2(": command not found\n", 2);
}

char	*get_executable_paths(char **path, char *command)
{
	char	*join;

	if (path && *command)
	{
		join = search_in_path(path, command);
		if (join)
			return (join);
	}
	print_command_not_found(command);
	return (NULL);
}
