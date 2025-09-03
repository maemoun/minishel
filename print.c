#include "./parsing/main.h"

const char *get_type_str(t_type type)
{
	if (type == PIPE)
		return "PIPE";
	if (type == RED_IN)
		return "RED_IN";
	if (type == RED_OUT)
		return "RED_OUT";
	if (type == HEREDOC)
		return "HEREDOC";
	if (type == APPEND)
		return "RED_APPEND";
	return "WORD";
}

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("[%s] has_space_after=%d, type=%s\n",
			tokens->value,
			tokens->has_space_after,
			get_type_str(tokens->type));
		tokens = tokens->next;
	}
}

void print_redirections(t_redirection *red)
{
    while (red)
    {
        printf("  RED: ");
        if (red->type == INPUT)
            printf("[INPUT] ->");
        else if (red->type == OUTPUT)
            printf("[OUTPUT] ->");
        else if (red->type == RED_HEREDOC)
            printf("[RED_HEREDOC] ->");
        else if (red->type == RED_APPEND)
            printf("[RED_APPEND] ->");
        printf("%s\n", red->name);
        red = red->next_red;
    }
}

void print_commands(t_command *cmds)
{
	int i = 1;
	while (cmds)
	{
		printf("COMMAND %d:\n", i);
		char **args = cmds->command;
		int j = 0;
		while (args && args[j])
		{
			printf("  ARG[%d]: %s\n", j, args[j]);
			j++;
		}
		t_redirection *red = cmds->red;
		while (red)
		{
			if (red->type == RED_HEREDOC)
				printf("  HEREDOC: %s (expand: %d)\n", red->name, red->expand_variable);
			else if (red->type == RED_APPEND)
				printf("  RED_APPEND: %s (expand: %d)\n", red->name, red->expand_variable);
			else if (red->type == INPUT)
				printf("  INPUT: %s (expand: %d)\n", red->name, red->expand_variable);
			else if (red->type == OUTPUT)
				printf("  OUTPUT: %s (expand: %d)\n", red->name, red->expand_variable);
			red = red->next_red;
		}
		cmds = cmds->next_command;
		i++;
	}
}

void	print_env_list(t_env *env_list)
{
    while (env_list)
    {
        printf("%s=%s\n", env_list->key, env_list->value);
        env_list = env_list->next;
    }
}