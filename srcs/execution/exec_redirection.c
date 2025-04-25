/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:28:24 by nadgalle          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:13 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_input_file_redirection(t_command *command)
{
	if (command->input_file && !command->redirect_heredoc)
	{
		if (command->input_fd == -1)
		{
			if (access(command->input_file, F_OK) == 0 && access(command->input_file, R_OK) == -1)
				ft_exit_free("Permission denied", EXIT_FAILURE, command, NULL);
			ft_exit_free(command->input_file, EXIT_FAILURE, command, NULL);
		}
		if (dup2(command->input_fd, STDIN_FILENO) == -1)
			ft_exit_free("redirection", EXIT_FAILURE, command, NULL);
		close(command->input_fd);
	}
	if (command->redirect_heredoc)
	{
		if (command->heredoc_fd == -1)
			ft_exit_free("here_doc", EXIT_FAILURE, command, NULL);
		if (dup2(command->heredoc_fd, STDIN_FILENO) == -1)
			ft_exit_free("redirection", EXIT_FAILURE, command, NULL);
		close(command->heredoc_fd);
	}
}

void output_file_redirection(t_command *command)
{
	if (command->output_file)
	{
		if (command->output_fd == -1)
		{
			if (access(command->output_file, F_OK) == 0 && access(command->output_file, W_OK) == -1)
			{
				ft_puterror(command->output_file, NULL, "Permission denied");
				ft_exit_free(NULL, 1, command, NULL);
			}
			ft_exit_free(command->output_file, EXIT_FAILURE, command, NULL);
		}
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
			ft_exit_free("redirection", EXIT_FAILURE, command, NULL);
		close(command->output_fd);
	}
	else if (command->next)
	{
		if (dup2(command->pipe_fd[1], STDOUT_FILENO) == -1)
			ft_exit_free("pipe", EXIT_FAILURE, command, NULL);
		close(command->pipe_fd[1]);
	}
}

void ft_handle_child_redirection(t_command *command)
{
	ft_input_file_redirection(command);
	output_file_redirection(command);
	if (command->pipe_fd[0] != -1)
		close(command->pipe_fd[0]);
	if (command->pipe_fd[1] != -1)
		close(command->pipe_fd[1]);
}

void ft_handle_parent_redirection(t_command *command)
{
	if (command->pipe_fd[1] != -1)
		close(command->pipe_fd[1]);
	if (command->input_fd != -1 && command->input_fd != STDIN_FILENO)
		close(command->input_fd);
	if (command->output_fd != -1 && command->output_fd != STDOUT_FILENO)
		close(command->output_fd);
	if (command->heredoc_fd != -1 && command->heredoc_fd != STDIN_FILENO)
		close(command->heredoc_fd);
	if (command->next)
	{
		if (command->pipe_fd[0] != -1)
		{
			if (dup2(command->pipe_fd[0], STDIN_FILENO) == -1)
				ft_exit_free("pipe", EXIT_FAILURE, command, NULL);
			close(command->pipe_fd[0]);
		}
	}
	else if (command->pipe_fd[0] != -1)
		close(command->pipe_fd[0]);
}
