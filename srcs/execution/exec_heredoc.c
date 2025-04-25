/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:31:26 by nadgalle          #+#    #+#             */
/*   Updated: 2025/04/09 11:51:31 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_open_file(int open_flag, t_command *command)
{
	int fd;

	fd = 0;
	if (open_flag == 0)
	{
		fd = open("srcs/EXECUTION/tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_exit_free("tmp", EXIT_FAILURE, command, NULL);
	}
	else if (open_flag == 1)
	{
		fd = open("srcs/EXECUTION/tmp", O_RDONLY);
		if (fd == -1)
			ft_exit_free("tmp", EXIT_FAILURE, command, NULL);
	}
	return (fd);
}

int ft_get_heredoc(char *limiter, t_command *command)
{
	int tmpfile_fd;
	char *limiter_n;

	tmpfile_fd = ft_open_file(0, command);
	limiter_n = ft_strjoin(limiter, "\n");
	ft_read_heredoc_content(limiter_n, tmpfile_fd);
	free(limiter_n);
	close(tmpfile_fd);
	tmpfile_fd = ft_open_file(1, command);
	return (tmpfile_fd);
}

void ft_read_heredoc_content(char *limiter_n, int tmpfile_fd)
{
	char *line;

	while (1)
	{
		ft_putstr_fd("pipe heredoc>", 1);
		line = get_next_line(0);
		if (!line)
		{
			printf("\n");
			break;
		}
		if (ft_strncmp(line, limiter_n, ft_strlen(limiter_n)) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, tmpfile_fd);
		free(line);
	}
}
