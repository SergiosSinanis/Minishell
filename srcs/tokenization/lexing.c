/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:45:43 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:55:53 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lexing_operator(t_token **head)
{
	t_token	*current;
	int		len;

	current = *head;
	len = 0;
	while (current)
	{
		len = ft_strlen(current->word);
		if (!len)
			return ;
		if (ft_strncmp(current->word, "<", 1) == 0 && len == 1)
			current->type = INPUT;
		else if (ft_strncmp(current->word, "<<", 2) == 0 && len == 2)
			current->type = HEREDOC;
		else if (ft_strncmp(current->word, ">", 1) == 0 && len == 1)
			current->type = OUTPUT_OVERWRITE;
		else if (ft_strncmp(current->word, ">>", 2) == 0 && len == 2)
			current->type = OUTPUT_APPEND;
		else if (ft_strncmp(current->word, "|", 1) == 0 && len == 1)
			current->type = PIPE;
		else if (ft_check_operator(current->word))
			current->type = OPERATOR_ERROR;
		current = current->next;
	}
}

void	ft_lexing_file(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if ((current->type >= INPUT && current->type <= OUTPUT_OVERWRITE)
			&& current->next)
		{
			if (current->next->type == 0)
				current->next->type = FILE;
		}
		current = current->next;
	}
}

void	ft_lexing_commands(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (current->type == 0)
			current->type = COMMAND;
		current = current->next;
	}
}

void	ft_lexer(t_token **head)
{
	ft_lexing_operator(head);
	ft_lexing_file(head);
	ft_lexing_commands(head);
}

char	**ft_add_to_array(char **arr, char *str)
{
	char	**new_arr;
	int		i;
	int		len;

	len = 0;
	if (arr)
	{
		while (arr[len])
			len++;
	}
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	if (arr)
		free(arr);
	return (new_arr);
}
