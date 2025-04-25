/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadgalle <nadgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:20:39 by nadgalle          #+#    #+#             */
/*   Updated: 2025/02/13 18:11:36 by nadgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_check_operator(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_operator(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_set_flags_word(char *str, char *charset, char *flags)
{
	int	in_word;
	int	i;

	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_is_in_charset(str[i], charset) && in_word == 0)
			in_word = 1;
		else if (ft_is_in_charset(str[i], charset))
			in_word = 0;
		flags[i] = in_word + '0';
		i++;
	}
}

int	ft_set_flags_quote(char *str, char *flags)
{
	int		in_quotes;
	char	quote;
	int		i;

	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]) && in_quotes == 0)
		{
			quote = str[i];
			in_quotes = 1;
		}
		else if (ft_is_quote(str[i]) && in_quotes == 1 && str[i] == quote)
			in_quotes = 0;
		if (flags[i] == '1' || in_quotes == 1)
			flags[i] = '1';
		i++;
	}
	if (in_quotes == 1)
		return (0);
	return (1);
}

char	*ft_set_flags(char *str, char *charset)
{
	char	*flags;
	int		i;

	flags = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	if (!flags)
		return (NULL);
	ft_set_flags_word(str, charset, flags);
	while (str[i])
	{
		if (ft_is_operator(str[i]))
			flags[i] = '2';
		i++;
	}
	if (ft_set_flags_quote(str, flags) == 0)
	{
		free(flags);
		return (ft_strdup("error"));
	}
	flags[ft_strlen(str)] = '\0';
	return (flags);
}
