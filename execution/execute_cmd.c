#include ".././parsing/main.h"

char	*check_if_exist_path(t_env *env_list, t_command *cmd)
{
	char	**full_path;

	full_path = NULL;
	if (ft_strchr_2(cmd->command[0], '/'))
	{
		if (access(cmd->command[0], F_OK) == 0
			&& access(cmd->command[0], X_OK) == -1)
			return (print_error(errno = EACCES, cmd->command[0], NULL), NULL);
		if (check_if_is_a_directory(cmd->command[0]))
			return (print_error(errno = EISDIR, cmd->command[0], NULL), NULL);
		if (!access(cmd->command[0], X_OK))
			return (ft_strdup_2(cmd->command[0]));
		if (access(cmd->command[0], F_OK))
			print_error(errno, cmd->command[0], NULL);
		return (NULL);
	}
	full_path = get_system_paths(env_list);
	if (!full_path)
	{
		if (!access(cmd->command[0], X_OK))
			return (ft_strdup(cmd->command[0]));
		else
			print_error(errno, cmd->command[0], NULL);
	}
	return (get_executable_paths(full_path, cmd->command[0]));
}

void	child_process(t_env *env_list, t_command *cmd)
{
	char	*path;
	char	**env;

	path = NULL;
	env = NULL;
	if (!ft_handle_redirection(cmd))
		exit(1);
	if (!setup_pipes(cmd))
		exit(1);
	if (!duplicate_std_fds(cmd))
		exit(1);
	if (is_builtin(cmd->command[0]))
		return (execute_builtin(cmd->command, cmd, env_list), exit(0));
	else
	{
		path = check_if_exist_path(env_list, cmd);
		if (!path)
			exit(127);
		env = build_environment_array(env_list);
		if (execve(path, cmd->command, env) == -1)
			return (print_error(errno, cmd->command[0], NULL),
				free(path), p2char(&env), exit(1));
	}
}

static void	close_current_fds(t_command *cmd)
{
	if (cmd->fd_pipe[1] > 0)
	{
		close(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
	if (cmd->fd_herdoc[0] > 0)
	{
		close(cmd->fd_herdoc[0]);
		cmd->fd_herdoc[0] = -1;
	}
}

void	parent_process(t_command *cmd)
{
	close_current_fds(cmd);
	if (cmd->prev)
	{
		if (cmd->prev->fd_pipe[0] > 0)
		{
			close(cmd->prev->fd_pipe[0]);
			cmd->prev->fd_pipe[0] = -1;
		}
		if (cmd->prev->prev)
		{
			if (cmd->prev->prev->fd_pipe[0] > 0)
			{
				close(cmd->prev->prev->fd_pipe[0]);
				cmd->prev->prev->fd_pipe[0] = -1;
			}
		}
	}
}

void	execute_cmd(t_command *cmd, t_env *env_list)
{
	t_command	*list;
	int			fork_pid;

	list = cmd;
	while (list)
	{
		if (list->next_command)
		{
			if (pipe(list->fd_pipe) == -1)
				return ;
		}
		fork_pid = fork();
		if (fork_pid < 0)
			perror(FORK_FAILD);
		if (fork_pid == 0)
		{
			set_signals_child();
			child_process(env_list, list);
		}
		else
			parent_process(list);
		list = list->next_command;
	}
	wait_and_exit(fork_pid);
}
