/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:18:41 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/17 16:27:45 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_validate_redirections(t_token *token, char **error_token)
{
	if ((token->type >= 3 && token->type <= 6))
	{
		if (!token->next)
		{
			*error_token = token->word;
			return (2);
		}
		if (token->next
			&& (token->next->type >= 3 && token->next->type <= 6))
		{
			*error_token = token->next->word;
			return (3);
		}
		if (token->next->type != FILE)
		{
			*error_token = token->word;
			return (2);
		}
		if (token->next && token->next->type == PIPE)
		{
			*error_token = "|";
			return (1);
		}
	}
	return (0);
}

void	ft_input_redirection(t_token *token, t_command *cmd)
{
	if (cmd->input_fd > 0)
		close(cmd->input_fd);
	free(cmd->input_file);
	if (cmd->redirect_heredoc == 1)
		cmd->redirect_heredoc = 0;
	cmd->input_file = ft_strdup(token->next->word);
	if (!ft_open_input_file(cmd, cmd->input_file))
	{
		cmd->input_fd = -1;
		return ;
	}
}

void	ft_output_redirection(t_token *token, t_command *cmd)
{
	if (cmd->output_fd > 0)
		close(cmd->output_fd);
	free(cmd->output_file);
	cmd->output_file = ft_strdup(token->next->word);
	if (!ft_open_output_file(cmd, cmd->output_file, token->type))
	{
		cmd->output_fd = -1;
		return ;
	}
}

void	ft_redirection(t_token *token, t_command *cmd)
{
	if (token->type == INPUT && token->next)
		ft_input_redirection(token, cmd);
	else if ((token->type == OUTPUT_OVERWRITE
			|| token->type == OUTPUT_APPEND) && token->next)
		ft_output_redirection(token, cmd);
	else if (token->type == HEREDOC && token->next)
		ft_heredoc(token, cmd);
}
