/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhualves <jhualves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:10:26 by jhualves          #+#    #+#             */
/*   Updated: 2025/05/26 23:45:32 by jhualves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft42/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>
# include <sys/fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>

# define ERR_SUCCESS_MSG "Success"
# define ERR_GENERAL_MSG "General error"
# define ERR_MISUSE_SHELL_MSG "Misuse of shell builtins"
# define ERR_CANT_EXECUTE_MSG "Command invoked cannot execute"
# define ERR_CMD_NOT_FOUND_MSG "Command not found"
# define ERR_EXIT_ARG_MSG "Invalid argument to exit"
# define ERR_CTRL_C_MSG "Script terminated by Ctrl-C"
# define ERR_KILL_9_MSG "Script terminated by kill -9"
# define ERR_SEGFAULT_MSG "Segmentation fault"
# define ERR_EXIT_RANGE_MSG "Exit status out of range"
# define ERR_UNKNOWN_MSG "Unknown error"
# define _POSIX_C_SOURCE 200809L

typedef enum e_alloc_type {
	ALLOC_TYPE_GENERIC,
	ALLOC_TYPE_CMD,
	ALLOC_TYPE_TOKEN,
	ALLOC_TYPE_REDIR,
	ALLOC_TYPE_STR,
	ALLOC_TYPE_STRING,
	ALLOC_TYPE_ENV_NODE,
	ALLOC_TYPE_CTX
}	t_alloc_type;

typedef enum e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	SQUOTE,
	DQUOTE,
	ENV_VAR,
	ASSIGNMENT_VAR,
	END,
	ERROR
}	t_token_type;

typedef enum e_redir_type {
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_redir_type;

typedef enum e_cmd_type {
	CMD_BUILTIN,
	CMD_EXTERNAL
}	t_cmd_type;

typedef struct s_redir {
	t_redir_type	type;
	char			*filename;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd {
	char			**args;
	char			*cmd_path;
	int				pipe[2];
	t_redir			*redirections;
	t_cmd_type		type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_allocation {
	void				*ptr;
	t_alloc_type		type;
	struct s_allocation	*next;
}	t_allocation;

typedef struct s_ctx {
	t_env					*env_list;
	t_cmd					*cmd_list;
	t_token					*token_list;
	char					*input;
	int						exit_status;
	int						previous_exit_status;
	int						current_exit_status;
	char					*last_error_message;
	t_allocation			*allocations;
	bool					is_interactive;
	char					*pwd;
	char					*oldpwd;
}	t_ctx;

// Protótipos de funções
// =============================================================================
// srcs/0.init_and clean_ctx/
// =============================================================================

// srcs/0.init_and_clean_ctx/free_ctx.c
void	free_context(t_ctx *ctx);
void	free_all_allocations(t_ctx *ctx);
void	super_free(t_ctx *ctx);
void	safe_free(t_ctx *ctx, void *ptr);

// srcs/0.init_and_clean_ctx/free_lists.c
void	free_redir_list(t_redir *redir);
void	free_cmd_list(t_cmd *cmd);
void	free_token_list(t_token *token);
void	free_string_array(char **array);
void	free_env_list(t_env *env_list); // Added prototype

// srcs/0.init_and_clean_ctx/init_ctx.c
t_ctx	*init_ctx(t_ctx *ctx, char **env);
void	init_environment(t_ctx *ctx, char **env_array);
void	add_env_node(t_ctx *ctx, t_env **list_head, const char *env_var);

// =============================================================================
// srcs/1.process_input/
// =============================================================================

// srcs/1.process_input/process_input.c
void	process_input(t_ctx *ctx, const char **input);

// =============================================================================
// srcs/2.tokenizer/
// =============================================================================

// srcs/2.tokenizer/handle_env_var.c
void	token_handle_env_var(t_ctx *ctx, const char **input, t_token **tokens);

// srcs/2.tokenizer/handle_pipe.c
void	token_handle_pipe(t_ctx *ctx, const char **input, t_token **tokens);

// srcs/2.tokenizer/handle_quote.c
void	token_handle_quote(t_ctx *ctx, const char **input, t_token **tokens);

// srcs/2.tokenizer/handle_redir.c
void	token_handle_redir(t_ctx *ctx, const char **input, t_token **tokens);

// srcs/2.tokenizer/handle_word.c
void	token_handle_word(t_ctx *ctx, const char **input, t_token **tokens);
int		is_valid_var_char(char c);


// srcs/2.tokenizer/tokenizer.c
t_token	*tokenize_input(t_ctx *ctx, const char **input);
void	ft_lstadd_back(t_token **head, t_token *new_node);
t_token	*new_token(t_ctx *ctx, t_token_type type, const char *str);

// =============================================================================
// srcs/3.syntax_validation/
// =============================================================================

// srcs/3.syntax_validation/syntax_validation.c
bool	validate_syntax(t_ctx *ctx, t_token *tokens);
// static bool	check_pipes(t_ctx *ctx, t_token *tokens); // Static
// static bool	check_redirections(t_ctx *ctx, t_token *tokens); // Static
// static bool	check_quotes(t_ctx *ctx, t_token *tokens); // Static

// =============================================================================
// srcs/4.parser/
// =============================================================================

// srcs/4.parser/handle_cmd.c
void	handle_pipe(t_ctx *ctx, t_token **tmp, t_cmd **current);
void	handle_redir(t_ctx *ctx, t_token **tmp, t_cmd *current);
void	handle_word(t_ctx *ctx, t_token **tmp, t_cmd *current);
void	handle_dquote(t_ctx *ctx, t_token **tmp, t_cmd *current);
void	handle_squote(t_ctx *ctx, t_token **tmp, t_cmd *current);

// srcs/4.parser/handle_cmd_1.c
void	handle_assignment_var(t_ctx *ctx, t_token **tmp, t_cmd *current);
void	handle_env_var(t_ctx *ctx, t_token **tmp, t_cmd *current);
void	handle_parse_error(t_ctx *ctx, t_token **tmp);

// srcs/4.parser/parsing.c
t_cmd	*parse_tokens(t_ctx *ctx, t_token **tokens);

// =============================================================================
// srcs/5.expander/
// =============================================================================

// srcs/5.expander/quotes_expánder.c
char	*expand_dquotes(t_ctx *ctx, const char *input);

// srcs/5.expander/var_expander.c
char	*expand_env_var(t_ctx *ctx, const char *input);
char	*get_env_value(t_ctx *ctx, const char *key);
char	*expand_string(t_ctx *ctx, const char *input);
int		var_name_length(const char *input);


// =============================================================================
// srcs/6.signals/
// =============================================================================

// srcs/6.signals/signals.c


// =============================================================================
// srcs/7.memory_mgmt/
// =============================================================================

// srcs/7.memory_mgmt/safe_malloc.c
void	*safe_malloc(t_ctx *ctx, size_t size, t_alloc_type type);
void	safe_free_all(t_ctx *ctx);

// =============================================================================
// srcs/8.error_mgmt/
// =============================================================================

// srcs/8.error_mgmt/print_error.c
char	*get_error_message(int error_code);
bool	handle_error(t_ctx *ctx, char *msg, int errnum, int exit_status);
bool	syntax_error(t_ctx *ctx, char *msg);
void	print_error(t_ctx *ctx, char *msg, int errnum, int exit_status);

// =============================================================================
// srcs/9.executor/
// =============================================================================
// File srcs/9.executor/executor.c was not found or accessible.

// =============================================================================
// srcs/12.handle_new_env/
// =============================================================================

// srcs/12.handle_new_env/create_new_env.c
t_env	*find_env_var(t_env *env_list, const char *key);
void	set_env_var(t_ctx *ctx, const char *assignment);
void	update_existing_var(t_ctx *ctx, t_env *var, const char *value);
void	add_new_env_var(t_ctx *ctx, t_env **env_list, char *key, char *value);

// srcs/12.handle_new_env/assignment_handler.c
void	process_assignments(t_ctx *ctx, t_cmd *cmd);
// static void	process_single_assignment(t_ctx *ctx, char *arg); // Static

// =============================================================================
// utils/
// =============================================================================

// utils/main_utils.c
void	process_minishell(t_ctx *ctx, char **input);
void	no_input(void);
void	input_null(t_ctx *ctx, char **input);

// utils/parsing_utils.c
void	add_arg(t_ctx *ctx, t_cmd *cmd, char *value);
void	add_redir(t_ctx *ctx, t_cmd *cmd, t_redir_type type, char *file);
t_cmd	*new_cmd(t_ctx *ctx);

// utils/safe_split.c
// static size_t	count_words(const char *s, char c);
// static char	*get_next_word(t_ctx *ctx, const char *s, char c, size_t *pos);
char	**safe_split(t_ctx *ctx, const char *s, char c);

// utils/safe_utils_libft.c
char	*safe_strdup(t_ctx *ctx, const char *s);
char	*ft_strjoin_free(t_ctx *ctx, char *s1, char *s2);
char	*ft_safe_strndup(t_ctx *ctx, const char *s, size_t size);
char	*safe_substr(t_ctx *ctx, char const *s, unsigned int start, size_t len);
char	*safe_strchr(t_ctx *ctx, const char *s, int c);
char	*safe_strrchr(t_ctx *ctx, const char *s, int c);
char	*safe_strnstr(t_ctx *ctx, const char *haystack, \
		const char *needle, size_t len);
char	*safe_strtrim(t_ctx *ctx, char const *s1, char const *set);
char	*safe_strjoin(t_ctx *ctx, char const *s1, char const *s2);

// utils/tokenizer_utils.c
int		define_substring(t_ctx *ctx, char **str,const char **input, \
		t_token_type type);
void	get_pid_var(t_ctx *ctx, char **str);

// =============================================================================
// minishell.c (main program file)
// =============================================================================
int		main(int argc, char **argv, char **env);
void	main_loop(t_ctx *ctx, char *input);

#endif