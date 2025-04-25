/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:50:52 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:56:04 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_token_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
}

t_token	*ft_create_node(char *word)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->word = ft_strdup(word);
	if (!new_node->word)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = 0;
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_token	*ft_array_to_list(char **tokens)
{
	t_token	*head;
	t_token	*current;
	t_token	*previous;
	int		i;

	if (!tokens || !tokens[0])
		return (NULL);
	head = ft_create_node(tokens[0]);
	if (!head)
		return (NULL);
	previous = head;
	i = 0;
	while (tokens[++i])
	{
		current = ft_create_node(tokens[i]);
		if (!current)
		{
			ft_free_token_list(head);
			return (NULL);
		}
		current->previous = previous;
		previous->next = current;
		previous = current;
	}
	return (head);
}

void	ft_print_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("token: %s\ntype: %d\n\n", current->word, current->type);
		current = current->next;
	}
}

// void	ft_print_command(t_command *head)
// {
// 	t_command	*current;
// 	int			i;

// 	current = head;
// 	while (current)
// 	{
// 		printf("\n==================node\n");
// 		printf("input file: %s fd=%d\n", current->input_file, current->input_fd);
// 		printf("output file: %s fd=%d\n",
// 			current->output_file, current->output_fd);
// 		printf("heredoc limiter: %s flag=%d\n",
// 			current->limiter, current->here_doc);
// 		i = 0;
// 		printf("command args:\n");
// 		if (!current->command_args || !current->command_args[0])
// 			return ;
// 		while (current->command_args[i])
// 		{
// 			printf("%s ", current->command_args[i]);
// 			printf("\n");
// 			i++;
// 		}
// 		current = current->next;
// 	}
// }
