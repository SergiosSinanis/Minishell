/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:31:38 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/07 16:45:44 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_chars_without_quotes(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && ft_is_quote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			count++;
		i++;
	}
	return (count);
}

char	*ft_copy_without_quotes(char *str)
{
	char	quote;
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_count_chars_without_quotes(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && ft_is_quote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*ft_process_quotes(char *str)
{
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = ft_copy_without_quotes(str);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	**ft_proc_tokens(char **tokens, char **new_tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		new_tokens[i] = ft_process_quotes(tokens[i]);
		if (!new_tokens[i])
		{
			while (i--)
				free(new_tokens[i]);
			free(new_tokens);
			return (NULL);
		}
		i++;
	}
	return (new_tokens);
}

char	**ft_unquote(char **tokens)
{
	int		len;
	char	**new_tokens;

	if (!tokens)
		return (NULL);
	len = 0;
	while (tokens[len])
		len++;
	new_tokens = malloc(sizeof(char *) * (len + 1));
	if (!new_tokens)
		return (NULL);
	if (ft_proc_tokens(tokens, new_tokens) == NULL)
		return (NULL);
	new_tokens[len] = NULL;
	return (new_tokens);
}
