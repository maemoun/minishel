/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:43:46 by abdo              #+#    #+#             */
/*   Updated: 2025/08/31 01:18:32 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "readline/readline.h"
# include "readline/history.h"

# define FORK_FAILD "fork failed"

typedef enum s_type
{
	PIPE,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND,
	WORD,
	DOUBLE_PIPE
}	t_type;

typedef struct s_parse_state
{
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;
	char	*new_str;
}	t_parse_state;

typedef struct s_token
{
	char			*value;
	int				has_space_after;
	t_type			type;
	int				has_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_exp
{
	const char	*src;
	char		*res;
	int			i;
	int			start;
	int			len;
}	t_exp;

typedef enum s_red_type
{
	INPUT,
	OUTPUT,
	RED_HEREDOC,
	RED_APPEND
}	t_red_type;

typedef struct s_redirection
{
	char					*name;
	t_red_type				type;
	int						expand_variable;
	struct s_redirection	*next_red;
}	t_redirection;

typedef struct s_data
{
	int	exit_status;
}	t_data;

typedef struct s_command
{
	char					**command;
	t_redirection			*red;
	int						fd_herdoc[2];
	int						cmd_backup[2];
	int						fd_cmd[2];
	int						fd_pipe[2];
	struct s_command		*next_command;
	struct s_command		*prev;
	t_data					*data;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			eg;
	struct s_env	*next;
	int				shlvl;
}	t_env;

typedef struct s_fir_expand_elements
{
	t_env	*env;
	int		last_exit_status;
	size_t	i;
	int		in_single;
	int		in_double;
	char	*result;
}	t_fir_expand_elements;

/* Token functions */
void			add_word_token(char *s, int *i, t_token **tokens);
t_token			*new_token(char *value, int is_space_before);
void			append_token(t_token **head, t_token *new_node);
void			assign_token_types(t_token *tokens);
t_token			*tokenize(char *s);
void			handle_exit(t_env *env_list, char *input);

/* Utils */
int				ft_isspace(char c);
int				ft_strlen(const char *s);
char			*my_strcat(char *dest, const char *src);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*my_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *s1);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_itoa(int n);
void			*ft_realloc(void *ptr, size_t new_size);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strndup(const char *s, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcat(char	*dest, const char	*src);

/* Print functions */
void			print_tokens(t_token *tokens);
void			print_commands(t_command *cmds);
void			print_env_list(t_env *env_list);

/* Check functions */
int				is_single_quoted(const char *str);
int				is_quoted(const char *str);
int				is_operator(char *str);
int				ft_is_valid_var_char(char c);
int				ft_isalnum(int c);
int				has_quote(const char *s);
int				is_quote(char c);
int				is_symbol(char c);
int				is_should_add_space_before(char *str, int pos);
int				check_syntax(t_token *tokens);
int				contains_unclosed_quote(const char *str);
int				print_syntax(const char *msg, t_type type);
char			*return_str(t_type type);

/* Parsing */
char			*add_spaces_around_symbols(char *input);
int				get_token_end(char *s, int i);
void			mark_heredoc_delimiters(t_token **tokens);
void			join_tokens_with_no_space(t_token **tokens);
char			*remove_quotes(const char *str);
t_redirection	*create_redirection(t_token *red_token, t_token *file_token,
					t_env *env, t_data *data);
t_command		*extract_all_commands(t_token *tokens, t_env *env,
					t_data *data);
char			**get_command_args(t_token **tokens);
void			append_redirection(t_redirection	**head,
					t_redirection	**last, t_redirection	*new_red);
t_redirection	*get_redirections(t_token **tokens, t_env *env,
					t_data *data);

/* Environment */
t_env			*init_env(char **envp);
// void			change_SHLVL(t_env **env_list);

/* Expansion */
void			expand_tokens(t_token **tokens, t_data *dt, t_env *env);
char			*expand_var(const char *src, t_data *dt, t_env *env);
char			*first_expand_variable(const char *input, t_env *env,
					int last_exit_status);
char			*first_get_env_value(char *key, t_env *env);
char			*expand_variable_name(const char *input,
					t_fir_expand_elements *st);
char			*expand_char_literal(t_fir_expand_elements *st, char c);
char			*expand_quote_state(const char *input,
					t_fir_expand_elements *st);
char			*expand_variable_name(const char *input,
					t_fir_expand_elements *st);
char			*f_expand_exit_status(t_fir_expand_elements *st);
char			*get_env_value(t_env *env, const char *key);
char			*expand_quote_state(const char *input,
					t_fir_expand_elements *st);
char			*expand_char_literal(t_fir_expand_elements *st, char c);
char			*extract_dollar_quote(const char *str);
char			*t_handle_dollar_quote(const char *str);
char			*append_str(char *dest, const char *src);
char			*append_char(char *str, char c);
int				is_var_char(char c);
char			*preprocess_escapes(const char *str);
char			*expand_exit_status(char *res, t_data *dt);
void			handle_variable(const char *input, t_fir_expand_elements *st);
void			handle_plain_char(const char *input, t_fir_expand_elements *st);
void			handle_quotes(const char *input, t_fir_expand_elements *st);
char			*expand_var_herdoc(const char *input,
					t_env *env, int last_exit_status);
void			handle_escaped_dollar(const char *input,
					t_fir_expand_elements *st);
void			set_signals_child(void);

/* Free functions */
void			free_tokens(t_token *list);
void			free_commands(t_command *cmd);
void			free_env_list(t_env *env);
void			clean_all_tokens(t_token *curr);

void			ft_signals(void);

//---------------------------//exeution//----------------------------//

//-----------//herdoc:

void			ft_exec_cmd(t_command *cmd, t_env *env_list);		
bool			ft_process_heredocs(t_command *cmd, t_env *env_list);
void			init_herdoc_fds(t_command *cmd);
bool			ft_create_herdoc(t_env *env_list,
					t_command *cmd, char *name, t_red_type type);
void			herdoc_read(t_command *cmd, char *name,
					t_env *env_list, t_red_type type);
char			*get_next_line(int fd);

//-----------//builtin:

bool			init_std_back(t_command *cmd);
int				is_builtin(char *cmd);
void			execute_builtin(char **command,
					t_command *cmd, t_env *env_list);
int				ft_echo(char **command);
int				ft_cd(t_env *env_list, char *path);
int				ft_env(t_env *env_list);
int				ft_exit(char **command, t_command *cmd, t_env *env_list);
char			*get_value(t_env *env_list, char *key);
int				ft_pwd(t_env *env_list);
int				ft_unset(char **command, t_env *env_list);
int				ft_export(char **command, t_command *cmd, t_env *env_list);
char			*get_valide_key(char *command);
void			add_export_list(t_env *env_list,
					char *value, char *key, bool eg);
void			desplay_list_export(t_env *env_list);
t_env			*ft_copy_env(t_env *env_list);
void			swap_nodes(t_env *node1, t_env *node2);

//-----------//redi:

bool			ft_handle_redirection(t_command *cmd);
bool			set_input(t_command *cmd, t_redirection *red_in);
bool			set_output(t_command *cmd, t_redirection *red_out);
bool			duplicate_std_fds(t_command *cmd);
bool			restore_std_input(t_command *cmd);
void			list_add_back(t_env **env_list, t_env *new);
t_env			*list_new_node(char *value, char *key, bool eg);

//-----------//print:

void			print_error(int error_nb, char *message, char *cmd);
void			file_error(int error_nb, char *message, char *cmd);

//-----------//utils:

void			close_fd(int *fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
int				ft_check_strcmp(const char *s1, const char *s2);
void			ft_putstr_fd2(char *s, int fd);
int				ft_strncmp_2(const char *s1, const char *s2, size_t n);
int				ft_strlen_2(const char *s);
char			*ft_strjoin_2(char const *s1, char const *s2);
char			*ft_strdup_2(const char *s1);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
char			*ft_substr_2(char const *s, unsigned int start, size_t len);
int				ft_isalpha_2(int c);
int				ft_isalnum_2(int c);
char			*ft_strchr_2(const char *s, int c);
char			**ft_split(const char *s, char c);

//-----------//exit:

int				ft_exit_status(int status);
void			cleanup_shell(t_command *cmd, t_env *env_list);
void			free_cmd_list(t_command *cmd);
void			free_cmd_node(t_command *cmd);
void			free_list_node(t_env *node);
void			free_redirec_list(t_redirection *red);
void			free_list(t_env **env_list);
void			free_list_node(t_env *node);
void			clear_all_pipes(t_command *cmd);
bool			wait_and_exit(int last_pid);
int				status_scan(int *status);

//-------------//signals:

void			ft_signals(void);
void			ctlc_handler(int sig);
void			ft_signals_child(void);

//------------//excute_cmd:

void			execute_cmd(t_command *cmd, t_env *env_list);
void			child_process(t_env *env_list, t_command *cmd);
bool			setup_pipes(t_command *cmd);
char			**build_environment_array(t_env *env_list);
char			*check_if_exist_path(t_env *env_list, t_command *cmd);
bool			check_if_is_a_directory(char *path);
char			**get_system_paths(t_env *env_list);
char			*get_executable_paths(char **path, char *command);
void			p2char(char ***ptr);

//-----------//print_test:

void			print_command_list(t_command *head);
void			print_command_debug(t_command *cmd);
void			print_commands(t_command *cmds);
#endif
