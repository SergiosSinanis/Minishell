/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:18:26 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/21 14:22:58 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_operator_errors(t_token *token_list, char **error_token)
{
	t_token	*current;
	int		error;

	current = token_list;
	while (current)
	{
		if (current->type == OPERATOR_ERROR)
		{
			*error_token = current->word;
			return (2);
		}
		error = ft_validate_redirections(current, error_token);
		if (error)
			return (error);
		current = current->next;
	}
	return (0);
}

char	*ft_redirection_error(char *token)
{
	if (ft_strncmp(token, ">>>>", 4) == 0)
		return (">>");
	if (ft_strncmp(token, ">>>", 3) == 0)
		return (">");
	if (ft_strncmp(token, ">>|", 3) == 0)
		return ("|");
	if (ft_strncmp(token, ">>", 2) == 0)
		return ("newline");
	if (ft_strncmp(token, ">", 1) == 0)
		return ("newline");
	if (ft_strncmp(token, "<<<<", 4) == 0)
		return ("<<");
	if (ft_strncmp(token, "<<<", 3) == 0)
		return ("<<");
	if (ft_strncmp(token, "<<", 2) == 0)
		return ("newline");
	if (ft_strncmp(token, "<", 1) == 0)
		return ("newline");
	return (token);
}
