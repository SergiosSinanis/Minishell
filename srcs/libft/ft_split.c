/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:04:29 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:04:06 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*ft_copy_word(const char *str, char c)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static void	ft_free_all(char **strs, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	skip(char const **s, char c)
{
	while (**s == c && **s != '\0')
		(*s)++;
	return (**s != '\0');
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;
	int		i;

	i = ((words = 0));
	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	while (skip(&s, c))
	{
		strs[i] = ft_copy_word(s, c);
		if (!strs[i])
		{
			ft_free_all(strs, i);
			return (NULL);
		}
		i++;
		while (*s && *s != c)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}
