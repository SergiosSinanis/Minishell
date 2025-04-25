/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:43:28 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/24 18:43:30 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_pipe_syntax(t_token *token_list)
{
	t_token	*current;

	if (!token_list || token_list->type == PIPE)
		return (1);
	current = token_list;
	while (current && current->next)
	{
		if (current->type == PIPE && current->next->type == PIPE)
			return (1);
		current = current->next;
	}
	if (current && current->type == PIPE)
		return (1);
	return (0);
}
