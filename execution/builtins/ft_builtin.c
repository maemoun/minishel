#include "../.././parsing/main.h"

bool	init_std_back(t_command *cmd)
{
	cmd->cmd_backup[0] = dup(STDIN_FILENO);
	cmd->cmd_backup[1] = dup(STDOUT_FILENO);
	if (cmd->cmd_backup[0] == -1 || cmd->cmd_backup[1] == -1)
		return (strerror(errno), false);
	return (true);
}

int	is_builtin(char *cmd)
{
	if (ft_check_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_check_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_check_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_check_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_check_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_check_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_check_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(char **command, t_command *cmd, t_env *env_list)
{
	if (ft_check_strcmp(command[0], "echo") == 0)
		ft_exit_status(ft_echo(command));
	else if (ft_check_strcmp(command[0], "cd") == 0)
		ft_exit_status(ft_cd(env_list, command[1]));
	else if (ft_check_strcmp(command[0], "env") == 0)
		ft_exit_status(ft_env(env_list));
	else if (ft_check_strcmp(command[0], "exit") == 0)
		ft_exit_status(ft_exit(command, cmd, env_list));
	else if (ft_check_strcmp(command[0], "export") == 0)
		ft_exit_status(ft_export(command, cmd, env_list));
	else if (ft_check_strcmp(command[0], "pwd") == 0)
		ft_exit_status(ft_pwd(env_list));
	else if (ft_check_strcmp(command[0], "unset") == 0)
		ft_exit_status(ft_unset(command, env_list));
	else
		return ;
}
