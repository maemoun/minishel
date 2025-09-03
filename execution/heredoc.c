#include ".././parsing/main.h"

static bool	heredoc_fork_failed(t_command *cmd, char *name_copy)
{
	free(name_copy);
	close_fd(&cmd->fd_herdoc[0]);
	close_fd(&cmd->fd_herdoc[1]);
	print_error(errno, NULL, NULL);
	return (false);
}

static void	heredoc_child_process(t_command *cmd, char *name_copy,
								t_env *env_list, t_red_type type)
{
	signal(SIGINT, ctlc_handler);
	herdoc_read(cmd, name_copy, env_list, type);
	free_cmd_list(cmd);
	free_list(&env_list);
	free(name_copy);
	exit(0);
}

static bool	heredoc_parent_process(t_command *cmd,
								char *name_copy, int fork_pid)
{
	free(name_copy);
	close_fd(&cmd->fd_herdoc[1]);
	if (wait_and_exit(fork_pid))
		return (false);
	return (true);
}

bool	ft_create_herdoc(t_env *env_list,
						t_command *cmd, char *name, t_red_type type)
{
	int		fork_pid;
	char	*name_copy;

	name_copy = ft_strdup_2(name);
	if (!name_copy)
		return (false);
	fork_pid = fork();
	if (fork_pid < 0)
		return (heredoc_fork_failed(cmd, name_copy));
	if (fork_pid == 0)
		heredoc_child_process(cmd, name_copy, env_list, type);
	return (heredoc_parent_process(cmd, name_copy, fork_pid));
}

bool	ft_process_heredocs(t_command *cmd, t_env *env_list)
{
	t_command		*tmp;
	t_redirection	*redi;

	tmp = cmd;
	init_herdoc_fds(cmd);
	while (tmp)
	{
		redi = tmp->red;
		while (redi)
		{
			if (redi->type == RED_HEREDOC)
			{
				if (tmp->fd_herdoc[0] != -1)
					close_fd(&tmp->fd_herdoc[0]);
				if (pipe(tmp->fd_herdoc) == -1)
					return (print_error(errno, NULL, NULL), false);
				if (!ft_create_herdoc(env_list, tmp, redi->name, redi->type))
					return (close_fd(&tmp->fd_herdoc[0]),
						close_fd(&tmp->fd_herdoc[1]), false);
			}
			redi = redi->next_red;
		}
		tmp = tmp->next_command;
	}
	return (true);
}
