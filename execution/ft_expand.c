#include ".././parsing/main.h"

char	*expand_variables_in_heredoc(char *token, t_command *cmd)
{
	t_exp	exp;

	init_expand(&exp);
	if (!token)
		return (NULL);
	exp.result = malloc(calculate_expanded_length(token, shell) + 1);
	if (!exp.result)
		return (NULL);
	while (token[exp.i])
	{
		exp.res = process_quotes_and_vars(token, &exp, shell);
		if (exp.res == 2)
			return (free(exp.result), ft_strdup_2("$\n"));
		if (exp.res == 3)
			return (free(exp.result), ft_strdup_2("minishell\n"));
		if (exp.res == 4)
			return (free(exp.result), exit_stats(&exp));
		if (exp.res > 0)
			continue ;
		exp.res = process_regular_chars(token, &exp);
		if (exp.res == -1)
			return (free(exp.result), ft_strdup_2(token));
	}
	exp.result[exp.j] = '\0';
	return (exp.result);
}

void	expand_cmd_heredoc(char **command, t_command *cmd, int fd)
{
	char	*expanded;

	if (!command || !env_list)
		return ;
	if (command[0])
	{
		expanded = expand_variables_in_heredoc(command[0], cmd);
		if (expanded)
		{
			ft_putstr_fd2(expanded, fd);
			free(expanded);
		}
	}
}
