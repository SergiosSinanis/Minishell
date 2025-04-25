/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:46:23 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/24 18:53:21 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*ft_create_commands(t_token *token_list, int *exit_status)
{
	int		error;
	char	*error_token;

	error_token = NULL;
	error = ft_check_operator_errors(token_list, &error_token);
	if (!token_list || error || ft_check_pipe_syntax(token_list))
	{
		if (error == 2 || error == 3)
			ft_print_parser_error(error, error_token, exit_status);
		else if (error == 1 || ft_check_pipe_syntax(token_list))
			ft_print_parser_error(1, NULL, exit_status);
		return (NULL);
	}
	return (ft_process_tokens(token_list));
}

t_command	*ft_process_tokens(t_token *token_list)
{
	t_command *first_cmd;
	t_command *current_cmd;
	t_token *current;

	first_cmd = ft_init_command();
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	current = token_list;
	while (current)
	{
		if (current->type == COMMAND)
			current_cmd->command_args = ft_add_to_array(current_cmd->command_args, current->word);
		else if (current->type >= 3 && current->type <= 6)
		{
			if (current_cmd->input_fd != -1 && current_cmd->output_fd != -1)
			{
				if (current->type >= 3 && current->type <= 6)
				{
					ft_redirection(current, current_cmd);
				}
			}
			current = current->next;
			continue;
		}
		else if (current->type == PIPE)
		{
			current_cmd->next = ft_init_command();
			if (!current_cmd->next)
			{
				ft_free_command_list(first_cmd);
				return (NULL);
			}
			current_cmd = current_cmd->next;
		}
		if (current)
			current = current->next;
	}
	return (ft_process_token_loop_heredoc(first_cmd));
}
