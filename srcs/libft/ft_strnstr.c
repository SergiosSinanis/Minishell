/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:33:25 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:04:58 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	b;
	char	*ptr;

	i = 0;
	ptr = 0;
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			ptr = (char *)haystack + i;
			b = 0;
			while (haystack[i + b] && haystack[i + b] == needle[b]
				&& i + b < len)
			{
				if (needle[b + 1] == '\0')
					return (ptr);
				b++;
			}
		}
		i++;
	}
	return (NULL);
}
