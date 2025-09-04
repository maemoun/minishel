#include ".././parsing/main.h"

void	init_herdoc_fds(t_command *cmd)
{
	t_command	*cur;

	cur = cmd;
	while (cur)
	{
		cur->fd_herdoc[0] = -1;
		cur->fd_herdoc[1] = -1;
		cur->fd_cmd[0] = -1;
		cur->fd_cmd[1] = -1;
		cur->fd_pipe[0] = -1;
		cur->fd_pipe[1] = -1;
		cur = cur->next_command;
	}
}

static void	expand_cmd_heredoc(char **line, t_command *cmd, int fd, t_env *env)
{
	char	*expanded_line;

	expanded_line = expand_var_herdoc(*line, env, cmd->data->exit_status);
	if (expanded_line)
	{
		ft_putstr_fd2(expanded_line, fd);
		ft_putstr_fd2("\n", fd);
		free(expanded_line);
		expanded_line = NULL;
	}
	else
	{
		ft_putstr_fd2(*line, fd);
		ft_putstr_fd2("\n", fd);
	}
}

static void	heredoc_write_line(char *line, t_command *cmd,
							t_env *env_list)
{
	if (cmd->red && cmd->red->expand_variable == 0)
	{
		ft_putstr_fd2(line, cmd->fd_herdoc[1]);
		ft_putstr_fd2("\n", cmd->fd_herdoc[1]);
	}
	else
		expand_cmd_heredoc(&line, cmd, cmd->fd_herdoc[1], env_list);
}

static void	heredoc_loop(t_command *cmd, char *name, t_env *env_list)
{
	char	*line;
	char	*line_without_quotes;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		line_without_quotes = remove_quotes(line);
		if (!ft_check_strcmp(line_without_quotes, name))
		{
			free(line);
			free(line_without_quotes);
			line = NULL;
			break ;
		}
		free(line_without_quotes);
		heredoc_write_line(line, cmd, env_list);
		free(line);
	}
}

void	herdoc_read(t_command *cmd, char *name,
					t_env *env_list, t_red_type type)
{
	if (!name)
		return ;
	close(cmd->fd_herdoc[0]);
	heredoc_loop(cmd, name, env_list);
	close(cmd->fd_herdoc[1]);
}
