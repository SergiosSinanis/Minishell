/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:24:22 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:54:43 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_open_input_file(t_command *cmd, char *filename)
{
	struct stat file_stat;

	if (stat(filename, &file_stat) == -1)
	{
		cmd->input_errno = errno;
		return (0);
	}
	if (S_ISDIR(file_stat.st_mode))
	{
		cmd->input_errno = EISDIR;
		return (0);
	}
	cmd->input_fd = open(filename, O_RDONLY);
	if (cmd->input_fd == -1)
	{
		cmd->input_errno = errno;
		return (0);
	}
	return (1);
}

int ft_open_output_file(t_command *cmd, char *filename, int type)
{
	int flags;
	struct stat file_stat;

	if (stat(filename, &file_stat) != -1)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			cmd->output_errno = EISDIR;
			return (0);
		}
	}
	if (type == OUTPUT_OVERWRITE)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	cmd->output_fd = open(filename, flags, 0644);
	if (cmd->output_fd == -1)
	{
		cmd->output_errno = errno;
		return (0);
	}
	return (1);
}

int ft_open_heredoc_file(t_command *cmd, char *limiter)
{
	if (cmd->last_heredoc == 1)
	{
		cmd->heredoc_fd = ft_get_heredoc(limiter, cmd);
		if (cmd->heredoc_fd == -1)
		{
			cmd->heredoc_errno = errno;
			return (0);
		}
		if (cmd->redirect_heredoc == 0)
			unlink("srcs/EXECUTION/tmp");
	}
	return (1);
}
