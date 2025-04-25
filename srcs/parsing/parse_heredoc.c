/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:52:20 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/24 18:52:22 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc(t_token *token, t_command *cmd)
{
	if (cmd->input_fd > 0)
		close(cmd->input_fd);
	cmd->here_doc = 1;
	cmd->redirect_heredoc = 1;
	if (cmd->limiter)
		free(cmd->limiter);
	cmd->limiter = ft_strdup(token->next->word);
}

t_command	*ft_process_token_loop_heredoc(t_command *command)
{
	t_command	*current;
	int			count;

	current = command;
	count = 0;
	while (current)
	{
		if (current->here_doc == 1)
			count++;
		current = current->next;
	}
	current = command;
	while (current)
	{
		if (count == 1 && current->here_doc == 1)
			current->last_heredoc = 1;
		if (current->here_doc == 1)
			count--;
		current = current->next;
	}
	current = command;
	while (current)
	{
		if (!ft_open_heredoc_file(current, current->limiter))
			break ;
		current = current->next;
	}
	return (command);
}
