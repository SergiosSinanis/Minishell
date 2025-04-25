/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:14:09 by nadgalle          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:41 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_execute_cmd(t_command *cmd, char **env, t_command **head)
{
	char *path;

	path = ft_get_path(cmd->command_args[0], env);
	if (!path)
	{
		ft_puterror(cmd->command_args[0], NULL, "command not found");
		ft_exit_free(NULL, 127, cmd, NULL);
	}
	ft_check_path(path, cmd);
	ft_reset_signals_for_child();
	if (execve(path, cmd->command_args, env) == -1)
	{
		if (path != cmd->command_args[0])
			free(path);
		ft_exit_free("execution", EXIT_FAILURE, cmd, head);
	}
}

void ft_exec_child(t_command *cmd, char **env, int *stat, t_command **head)
{
	ft_handle_child_redirection(cmd);
	ft_reset_signals_for_child();
	if (cmd->command_args)
	{
		if (ft_isbuiltin(cmd->command_args[0]))
		{
			ft_exec_builtin(cmd->command_args, &env, stat, 0);
			ft_close_inherited_fds();
			ft_free_command_list(*head);
			exit(*stat);
		}
		else
		{
			ft_close_inherited_fds();
			ft_execute_cmd(cmd, env, head);
		}
	}
}

pid_t ft_exec(t_command *cmd, char **env, int *exit_status, t_command **head)
{
	pid_t pid;

	if (cmd->next && pipe(cmd->pipe_fd) == -1)
		ft_exit_free("pipe", EXIT_FAILURE, cmd, NULL);
	else if (!cmd->next)
	{
		cmd->pipe_fd[0] = -1;
		cmd->pipe_fd[1] = -1;
	}
	pid = fork();
	if (pid == -1)
		ft_exit_free("fork", EXIT_FAILURE, cmd, NULL);
	if (pid == 0)
	{
		signal(SIGPIPE, SIG_DFL);
		ft_exec_child(cmd, env, exit_status, head);
	}
	else
		ft_handle_parent_redirection(cmd);
	if (cmd->redirect_heredoc && cmd->last_heredoc)
	{
		close(cmd->heredoc_fd);
		unlink("srcs/EXECUTION/tmp");
	}
	return (pid);
}

void ft_exec_loop(t_command **cmd, char **env, int *exit, int *last_code)
{
	t_command *current;
	int status;

	status = 0;
	current = *cmd;
	while (current)
	{
		current->pid = ft_exec(current, env, exit, cmd);
		current = current->next;
	}
	current = *cmd;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			*last_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			*last_code = 128 + WTERMSIG(status);
		if (*last_code == 128 + SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (last_code != 0)
			*exit = *last_code;
		current = current->next;
	}
}

void ft_exec_all(t_command **commands, char **env, int *exit_status)
{
	int last_exit_code;
	int saved_stdin;
	int saved_stdout;

	last_exit_code = 0;
	if (!commands || !*commands)
	{
		*exit_status = 1;
		return;
	}
	if ((*commands)->command_args)
	{
		if ((*commands)->next == NULL && ft_isbuiltin((*commands)->command_args[0]))
			return;
	}
	ft_setup_signal_handling();
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	ft_exec_loop(commands, env, exit_status, &last_exit_code);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	*exit_status = last_exit_code;
}
