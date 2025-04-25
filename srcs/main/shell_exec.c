/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:37:28 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:53:56 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_shell_exec(t_token *token_list, char **new_tokens, char ***env, int exit_status)
{
	exit_status = ft_process_commands(token_list, env, exit_status);
	ft_free_token_list(token_list);
	ft_free_tab(new_tokens);
	return (exit_status);
}

int ft_process_commands(t_token *token_list, char ***env, int exit_status)
{
	t_command *commands;

	ft_lexer(&token_list);
	commands = ft_create_commands(token_list, &exit_status);
	if (!commands)
		return (exit_status);
	if (commands->command_args && commands->next == NULL && ft_isbuiltin(commands->command_args[0]))
	{
		if (ft_check_redirection(commands, &exit_status) != 0)
			ft_exec_builtin(commands->command_args, env, &exit_status,
							commands->output_fd);
	}
	ft_exec_all(&commands, *env, &exit_status);
	ft_free_command_list(commands);
	return (exit_status);
}
