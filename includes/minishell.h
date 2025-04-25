/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:16:02 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:48:34 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

#include "../srcs/libft/libft.h"
#include "../srcs/gnl/get_next_line.h"

#define COMMAND 1
#define FILE 2
#define INPUT 3
#define HEREDOC 4
#define OUTPUT_APPEND 5
#define OUTPUT_OVERWRITE 6
#define PIPE 7
#define OPERATOR_ERROR -1

typedef struct s_expand_context
{
	int exit_status;
	char *new_str;
	char **env;
} t_expand_context;

typedef struct s_command
{
	char **command_args;
	char *input_file;
	int input_fd;
	int input_errno;
	char *output_file;
	int output_fd;
	int output_errno;
	int here_doc;
	char *limiter;
	int heredoc_fd;
	int heredoc_errno;
	int last_heredoc;
	int redirect_heredoc;
	int pipe_fd[2];
	int error_code;
	pid_t pid;
	struct s_command *next;
} t_command;

typedef struct s_token
{
	char *word;
	int type;
	struct s_token *previous;
	struct s_token *next;
} t_token;

typedef struct s_shell_state
{
	char *input;
	char ***env;
	int exit_status;
	t_token *token_list;
	char **new_tokens;
} t_shell_state;

typedef struct s_execdata
{
	int last_exit_code;
	int saved_stdin;
	int saved_stdout;
} t_execdata;

// Utils
void ft_puterror(char *cmd, char *cmd2, char *error);
void ft_free_token_list(t_token *head);
void ft_free_tab(char **tab);
void *ft_realloc(void *ptr, size_t oldsize, size_t newsize, int free_f);
char *ft_itoa(int nbr);
int ft_is_str_whitespace(char *str);

// Builtins

void ft_echo(char **tokens, int output_fd);
void ft_exit(char **tokens, int *exit_status);
void ft_env(char **envp, int output_fd);
void ft_pwd(int output_fd, char **tokens, int *exit);
void ft_cd_invalid_opt(char **tokens, int *exit, char **env);
void ft_cd(char **tokens, int *exit_status, char **env);
void ft_print_tok(char **tokens, size_t i, int output_fd);
void ft_parse_flags(char **tokens, size_t *i, int *print_newline);
void ft_swap(char **s1, char **s2);
void ft_exec_builtin(char **tokens, char ***envp, int *exit, int fd);
char *ft_strdup2(char *src, int n);
char **ft_duplicate_env(char **envp);
char **ft_export(char **envp, char **tokens, int *exit, int fd);
char **ft_sort_env(char **env, int output_fd);
char **ft_minimal_env(char **envp);
char **ft_unset(char **envp, char **tokens, int *exit_status);
int ft_extract_key_value(char *token, char **key, char **value);
int ft_replace_env_var(char **envp, char *key, char *value);
int ft_add_new_env_var(char ***envp, char *key, char *value);
int ft_isbuiltin(char *str);
int ft_check_path_builtin(char *path, int *exit_code);
int ft_check_redirection(t_command *command, int *exit_code);
int ft_error_builtin(char *path, char *error, int code, int *exit);
int ft_check_path_builtin(char *path, int *exit_code);
int ft_tab_size(char **tab);
int ft_tab_check_home(char **env);
int ft_check_option(int *exit_status, char **tokens);

// Execution

void ft_check_path(char *path, t_command *command);
void ft_close_inherited_fds(void);
void ft_exec_all(t_command **commands, char **env, int *exit_status);
void ft_exit_error(char *path, char *error, int code, t_command *cmd);
void ft_exit_free(char *msg, int exit, t_command *cmd, t_command **head);
void ft_execute_cmd(t_command *cmd, char **env, t_command **head);
void ft_handle_parent_redirection(t_command *command);
void ft_input_file_redirection(t_command *command);
void ft_handle_child_redirection(t_command *command);
void ft_exec_child(t_command *cmd, char **env, int *stat, t_command **head);
void ft_read_heredoc_content(char *limiter_n, int tmpfile_fd);
char *ft_get_path(char *cmd, char **env);
int ft_open_file(int open_flag, t_command *command);
int ft_get_heredoc(char *limiter, t_command *command);

// Expand and unquote

void ft_update_quote_flags(char c, int *flag_single, int *flag_double);
char *ft_dollar(char *str, int *i, t_expand_context *context);
char *ft_expand(char *str, char **env, int exit_status);
char *ft_get_env_variable(const char *var_name, char **env);
char *ft_append_char(char *str, char c);
char *ft_question_mark(char *new_str, int exit_status);
char *ft_copy_without_quotes(char *str);
char *ft_process_quotes(char *str);
char **ft_unquote(char **tokens);
char **ft_proc_tokens(char **tokens, char **new_tokens);
int ft_count_digits(int nb);
int ft_count_chars_without_quotes(char *str);
int ft_is_number(char *argv);

// Main

char *ft_shell_expansion(char *input, char **env, int exit_status);
char **ft_setup_environment(char **envp);
int ft_process_commands(t_token *token_list, char ***env, int exit);
int ft_shell_input(char **input);
int ft_shell_special_input(char *input);
int ft_shell_token(char *expand, t_token **token, char ***new_tokens);
int ft_shell_exec(t_token *token, char **new_tokens, char ***env, int exit);
int ft_shell_process_first_half(char **input, int *exit_status);
int ft_shell_process_second_half(t_shell_state *state);
int ft_shell_loop(char ***env);

// Parsing

void ft_free_command_list(t_command *cmd_list);
void ft_input_redirection(t_token *token, t_command *cmd);
void ft_output_redirection(t_token *token, t_command *cmd);
void ft_heredoc(t_token *token, t_command *cmd);
void ft_redirection(t_token *token, t_command *cmd);
void ft_print_parser_error(int error, char *token, int *exit);
char *ft_redirection_error(char *token);
int ft_is_quote(char c);
int ft_check_operator_errors(t_token *token_list, char **error_token);
int ft_validate_redirections(t_token *token, char **error_token);
int ft_check_pipe_syntax(t_token *token_list);
int ft_open_input_file(t_command *cmd, char *filename);
int ft_open_output_file(t_command *cmd, char *filename, int type);
int ft_open_heredoc_file(t_command *cmd, char *limiter);
t_command *ft_process_tokens(t_token *token_list);
t_command *ft_init_command(void);
t_command *ft_create_commands(t_token *token_list, int *exit);
t_command *ft_process_token_loop_heredoc(t_command *command);

// Signals

void ft_sigint(int sig);
void ft_setup_signals(void);
void ft_reset_signals_for_child(void);
void ft_setup_signal_handling(void);
void ft_handle_signals(int enable);

// Tokenization and lexing

void ft_set_flags_word(char *str, char *charset, char *flags);
void ft_lexing_operator(t_token **head);
void ft_lexing_file(t_token **head);
void ft_lexing_commands(t_token **head);
void ft_lexer(t_token **head);
char *ft_str_cpy_i(char *dest, const char *src, int index, int *len);
char **ft_add_words(char **res, char *str, char *charset, char *flag);
char **ft_split_args(char *str, char *charset);
char **ft_add_to_array(char **arr, char *str);
char *ft_set_flags(char *str, char *charset);
int ft_is_in_charset(char c, char *charset);
int ft_count_words(char *str, char *charset);
int ft_is_operator(char c);
int ft_check_operator(char *str);
int ft_set_flags_quote(char *str, char *flags);
t_token *ft_array_to_list(char **tokens);
t_token *ft_tokenize_input(char *input_expand, char ***new_tokens);

#endif
