/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:33:45 by nadgalle          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:29 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_exit_error(char *path, char *error, int code, t_command *cmd)
{
	ft_puterror(path, NULL, error);
	ft_exit_free(NULL, code, cmd, NULL);
}

void ft_free_command(t_command *command)
{
	if (command)
	{
		if (command->input_file)
			free(command->input_file);
		if (command->output_file)
			free(command->output_file);
		if (command->limiter)
			free(command->limiter);
		if (command->input_fd > 2)
			close(command->input_fd);
		if (command->output_fd > 2)
			close(command->output_fd);
		if (command->command_args)
			ft_free_tab(command->command_args);
	}
	ft_close_inherited_fds();
}

void ft_exit_free(char *msg, int status, t_command *cmd, t_command **head)
{
	t_command *current;

	if (msg)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(msg);
	}
	if (!head)
		ft_free_command(cmd);
	else
	{
		current = *head;
		while (current)
		{
			ft_free_command(current);
			current = current->next;
		}
		free(head);
	}
	exit(status);
}

void ft_close_inherited_fds(void)
{
	int fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void ft_setup_signal_handling(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGPIPE, &sa, NULL);
}
