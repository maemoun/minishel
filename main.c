/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:46:31 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 00:46:12 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/main.h"

t_command	*parser(char *s, t_data *dt, t_env *env_list, t_token **t)
{
	t_token		*tokens;
	t_command	*cmds;

	(void)t;
	tokens = tokenize(s);
	assign_token_types(tokens);
	mark_heredoc_delimiters(&tokens);
	if (check_syntax(tokens) == 258)
	{
		dt->exit_status = 258;
		free_tokens(tokens);
		return (NULL);
	}
	expand_tokens(&tokens, dt, env_list);
	join_tokens_with_no_space(&tokens);
	cmds = extract_all_commands(tokens, env_list, dt);
	free_tokens(tokens);
	return (cmds);
}

static char	*get_input(t_env *env_list)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		handle_exit(env_list, input);
	add_history(input);
	return (input);
}

static t_command	*prepare_command(char *input,
		t_data *dt, t_env *env_list, t_token **tokens)
{
	char		*tmp;
	char		*line;
	t_command	*cmd;

	tmp = add_spaces_around_symbols(input);
	free(input);
	line = first_expand_variable(tmp, env_list, 0);
	free(tmp);
	cmd = parser(line, dt, env_list, tokens);
	free(line);
	return (cmd);
}

int	minishell(t_data *dt, t_env *env_list)
{
	t_command	*cmd;
	char		*input;
	t_token		*tokens;

	tokens = NULL;
	while (1)
	{
		input = get_input(env_list);
		cmd = prepare_command(input, dt, env_list, &tokens);
		if (!cmd)
		{
			free_tokens(tokens);
			continue ;
		}
		ft_exec_cmd(cmd, env_list);
		dt->exit_status = 0;
		free_commands(cmd);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	dt;
	t_env	*env_list;

	env_list = init_env(envp);
	(void)ac;
	(void)av;
	dt.exit_status = 0;
	ft_signals();
	minishell(&dt, env_list);
	return (0);
}
