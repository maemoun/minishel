#include ".././parsing/main.h"

bool	restore_std_input(t_command *cmd)
{
	if (dup2(cmd->cmd_backup[0], STDIN_FILENO) == -1)
		return (strerror(errno), false);
	close(cmd->cmd_backup[0]);
	if (dup2(cmd->cmd_backup[1], STDOUT_FILENO) == -1)
		return (strerror(errno), false);
	close(cmd->cmd_backup[1]);
	return (true);
}

void	ft_exec_cmd(t_command *cmd, t_env *env_list)
{
	signal(SIGQUIT, SIG_IGN);
	if (!ft_process_heredocs(cmd, env_list))
		return ;
	if (is_builtin(cmd->command[0]) && !cmd->next_command)
	{
		init_std_back(cmd);
		if (!ft_handle_redirection(cmd))
			return ;
		if (!duplicate_std_fds(cmd))
			return (restore_std_input(cmd), close_fd(&cmd->fd_herdoc[0]));
		execute_builtin(cmd->command, cmd, env_list);
		restore_std_input(cmd);
	}
	else
	{
		execute_cmd(cmd, env_list);
	}
}
