/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:30:49 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:54:22 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_shell_loop(char ***env)
{
	t_shell_state state;
	int result;

	state.env = env;
	state.exit_status = 0;
	while (1)
	{
		result = ft_shell_process_first_half(&state.input, &state.exit_status);
		if (result == -1)
			break;
		if (result == 1)
			continue;
		result = ft_shell_process_second_half(&state);
		if (result == 1)
			continue;
		state.exit_status = ft_shell_exec(state.token_list,
										  state.new_tokens, state.env, state.exit_status);
	}
	return (state.exit_status);
}

int ft_shell_process_first_half(char **input, int *exit_status)
{
	int status;

	if (ft_shell_input(input) == -1)
		return (-1);
	status = ft_shell_special_input(*input);
	if (status >= 0)
	{
		if (status == 1)
			*exit_status = 0;
		else
			*exit_status = status;
		return (1);
	}
	add_history(*input);
	return (0);
}

int ft_shell_process_second_half(t_shell_state *state)
{
	char *input_expand;

	input_expand = ft_shell_expansion(state->input,
									  *state->env, state->exit_status);
	if (!input_expand)
		return (1);
	if (ft_shell_token(input_expand, &(state->token_list),
					   &(state->new_tokens)))
		return (1);
	return (0);
}
