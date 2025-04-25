/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:36:19 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:05:10 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	start_word(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
			start++;
	return (start);
}

static	size_t	end_word(char const *s1, char const *set, size_t start)
{
	size_t	end;

	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
			end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = start_word(s1, set);
	end = end_word(s1, set, start);
	result = (char *)malloc(end - start + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (start < end)
	{
		result[i] = s1[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}
