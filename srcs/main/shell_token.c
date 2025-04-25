/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:11:17 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/24 18:38:41 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_shell_token(char *input_expand, t_token **token_list, char ***new_tokens)
{
	*token_list = ft_tokenize_input(input_expand, new_tokens);
	if (!*token_list)
	{
		free(input_expand);
		return (1);
	}
	free(input_expand);
	return (0);
}

t_token	*ft_tokenize_input(char *input_expand, char ***new_tokens)
{
	char	**tokens;
	t_token	*token_list;

	tokens = ft_split_args(input_expand, " \t");
	if (!*tokens || !tokens)
		return (NULL);
	*new_tokens = ft_unquote(tokens);
	token_list = ft_array_to_list(*new_tokens);
	ft_free_tab(tokens);
	return (token_list);
}
