/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:08:36 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:55:25 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*ft_init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command_args = NULL;
	cmd->input_file = NULL;
	cmd->input_fd = 0;
	cmd->input_errno = 0;
	cmd->output_file = NULL;
	cmd->output_fd = 0;
	cmd->output_errno = 0;
	cmd->here_doc = 0;
	cmd->limiter = NULL;
	cmd->heredoc_fd = 0;
	cmd->last_heredoc = 0;
	cmd->redirect_heredoc = 0;
	cmd->error_code = 0;
	cmd->pid = 0;
	cmd->pipe_fd[0] = 0;
	cmd->pipe_fd[1] = 0;
	cmd->next = NULL;
	return (cmd);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	ft_print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
}

void	ft_print_parser_error(int error_type, char *token, int *exit_status)
{
	char	*error_token;

	error_token = NULL;
	if (error_type == 1)
		ft_print_syntax_error("|");
	else if (error_type == 3)
		ft_print_syntax_error(token);
	else if (error_type == 2)
	{
		if (token)
		{
			error_token = ft_redirection_error(token);
			if (ft_strncmp(token, "|", 1) == 0)
				error_token = "|";
			ft_print_syntax_error(error_token);
		}
		else
			ft_print_syntax_error("newline");
	}
	*exit_status = 2;
}

void	ft_free_command_list(t_command *cmd_list)
{
	t_command	*temp;
	int			i;

	while (cmd_list)
	{
		temp = cmd_list->next;
		if (cmd_list->command_args)
		{
			i = 0;
			while (cmd_list->command_args[i])
				free(cmd_list->command_args[i++]);
			free(cmd_list->command_args);
		}
		if (cmd_list->input_fd > 0)
			close(cmd_list->input_fd);
		if (cmd_list->output_fd > 0)
			close(cmd_list->output_fd);
		free(cmd_list->input_file);
		free(cmd_list->output_file);
		free(cmd_list->limiter);
		free(cmd_list);
		cmd_list = temp;
	}
}
