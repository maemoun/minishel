#include ".././parsing/main.h"

bool	setup_pipes(t_command *cmd)
{
	if (cmd->fd_cmd[1] != STDOUT_FILENO && cmd->fd_pipe[1] > 0)
	{
		close(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
	else if (cmd->fd_cmd[1] == STDOUT_FILENO
		&& cmd->next_command && cmd->fd_pipe[1] > 0)
		cmd->fd_cmd[1] = cmd->fd_pipe[1];
	if (cmd->prev && cmd->fd_cmd[0] == STDIN_FILENO)
		cmd->fd_cmd[0] = cmd->prev->fd_pipe[0];
	if (cmd->fd_pipe[0] != -1)
	{
		close(cmd->fd_pipe[0]);
		cmd->fd_pipe[0] = -1;
	}
	return (true);
}

bool	duplicate_std_fds(t_command *cmd)
{
	if (cmd->fd_cmd[0] != STDIN_FILENO)
	{
		if (dup2(cmd->fd_cmd[0], STDIN_FILENO) == -1)
		{
			close(cmd->fd_cmd[0]);
			return (print_error(errno, NULL, NULL), false);
		}
		close(cmd->fd_cmd[0]);
	}
	if (cmd->fd_cmd[1] != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_cmd[1], STDOUT_FILENO) == -1)
		{
			close(cmd->fd_cmd[1]);
			return (print_error(errno, NULL, NULL), false);
		}
		close(cmd->fd_cmd[1]);
	}
	return (true);
}

bool	set_input(t_command *cmd, t_redirection *red_in)
{
	if (cmd->fd_cmd[0] != STDIN_FILENO && cmd->fd_cmd[0] != cmd->fd_herdoc[0])
		close(cmd->fd_cmd[0]);
	if (red_in->type == INPUT)
	{
		cmd->fd_cmd[0] = open(red_in->name, O_RDONLY, 0777);
		if (cmd->fd_cmd[0] == -1)
			return (print_error(errno, red_in->name, NULL), false);
	}
	else
		cmd->fd_cmd[0] = cmd->fd_herdoc[0];
	return (true);
}

bool	set_output(t_command *cmd, t_redirection *red_out)
{
	if (cmd->fd_cmd[1] != STDOUT_FILENO)
	{
		close(cmd->fd_cmd[1]);
		cmd->fd_cmd[1] = -1;
	}
	if (red_out->type == OUTPUT)
	{
		cmd->fd_cmd[1] = open(red_out->name, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (cmd->fd_cmd[1] == -1)
			return (print_error(errno, red_out->name, NULL), false);
	}
	else
	{
		cmd->fd_cmd[1] = open(red_out->name, O_CREAT | O_APPEND | O_RDWR, 0777);
		if (cmd->fd_cmd[1] == -1)
			return (print_error(errno, red_out->name, NULL), false);
	}
	return (true);
}

bool	ft_handle_redirection(t_command *cmd)
{
	t_redirection	*redi;

	redi = cmd->red;
	cmd->fd_cmd[0] = STDIN_FILENO;
	cmd->fd_cmd[1] = STDOUT_FILENO;
	while (redi)
	{
		if (redi->type == INPUT || redi->type == RED_HEREDOC)
			if (!set_input(cmd, redi))
				return (false);
		if (redi->type == OUTPUT || redi->type == RED_APPEND)
			if (!set_output(cmd, redi))
				return (false);
		redi = redi->next_red;
	}
	if (cmd->fd_cmd[0] != cmd->fd_herdoc[0])
	{
		close(cmd->fd_herdoc[0]);
		cmd->fd_herdoc[0] = -1;
	}
	return (true);
}
