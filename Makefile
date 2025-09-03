# ==================== VARIABLES ====================
NAME    := minishel
CC      := cc

# LIBPATH = /Users/sabderra/.local/readline
FLAGS   = -Wall -Wextra -Werror -I.
LDFLAGS = -lreadline

SRC     := main.c \
			print.c \
		   ./parsing/tokenization/tokens.c \
		   ./parsing/tokenization/join_tokens.c \
		   ./parsing/tokenization/add_spaces.c \
		   ./parsing/tokenization/remove_quotes.c \
		   ./parsing/tokenization/mark_delimiters.c \
		   ./parsing/tokenization/get_token_end.c \
		   ./parsing/expand/expand.c \
		   ./parsing/expand/handle_dollar_quote.c \
		   ./parsing/expand/expand_append.c \
		   ./parsing/expand/first_expand_utils.c \
		   ./parsing/expand/first_expand.c \
		   ./parsing/expand/expand_var.c \
		   ./parsing/parsing_utils/utils1.c \
		   ./parsing/parsing_utils/utils2.c \
		   ./parsing/parsing_utils/utils3.c \
		   ./parsing/parsing_utils/is_funcs1.c \
		   ./parsing/parsing_utils/is_funcs2.c \
		   ./parsing/syntax/syntax_errors.c \
		   ./parsing/syntax/syntax_utils.c \
		   ./parsing/command_core/get_command_args.c \
		   ./parsing/command_core/get_redirections.c \
		   ./parsing/command_core/create_redirection.c \
		   ./parsing/command_core/extract_all_commands.c \
		   ./parsing/others/handle_exit.c \
		   ./parsing/others/init_env.c \
		   ./parsing/others/free.c \
		   ./parsing/others/signals.c \
		   ./execution/ft_execution.c \
		   ./execution/heredoc.c \
		   ./execution/herdoc_expand.c \
		   ./execution/ft_utils_1.c \
		   ./execution/ft_print.c \
		   ./execution/ft_redirection.c \
		   ./execution/builtins/ft_builtin.c \
		   ./execution/exit_status.c \
		   ./execution/builtins/built_echo.c \
		   ./execution/builtins/built_cd.c \
		   ./execution/builtins/built_env.c \
		   ./execution/builtins/built_exit.c \
		   ./execution/builtins/built_pwd.c \
		   ./execution/builtins/built_unset.c \
		   ./execution/builtins/built_export.c \
		   ./execution/builtins/ft_export_utils.c \
		   ./execution/execute_cmd.c \
		   ./execution/ft_split.c \
		   ./execution/ft_signals_child.c \
		   ./execution/builtins/ft_export_utils_2.c \
		   ./execution/ft_utils_2.c \
		   ./execution/ft_utils_3.c \
		   ./execution/execute_cmd_utils.c \
		   ./execution/free.c \
		   ./execution/herdoc_read.c \
		   ./execution/ft_get_path.c \
		   #print.c

OBJ     := $(SRC:.c=.o)

# ==================== TARGETS ====================
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c main.h
	$(CC) $(FLAGS) -c $< -o $@

# ==================== CLEANING ====================
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

me: fclean all
	./$(NAME)

# ==================== ========= ====================
