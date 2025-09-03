#include "../.././parsing/main.h"

int	ft_is_numeric(char *command)
{
	int	i;

	if (!command || *command == '\0')
		return (0);
	i = 0;
	if (command[i] == '-' || command[i] == '+')
		i++;
	while (command[i])
	{
		if (!ft_isdigit(command[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **command, t_command *cmd, t_env *env_list)
{
	printf("exit\n");
	if (command && command[1])
	{
		if (command[2] && ft_is_numeric(command[1]))
		{
			ft_putstr_fd2("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		if (!ft_is_numeric(command[1]))
		{
			ft_putstr_fd2("minishell: exit: ", 2);
			ft_putstr_fd2(command[1], 2);
			ft_putstr_fd2("numeric argument required\n", 2);
			exit(255);
		}
		else
			ft_exit_status(ft_atoi(command[1]));
	}
	else
		ft_exit_status(0);
	cleanup_shell(cmd, env_list);
	exit(ft_exit_status(-1));
}
