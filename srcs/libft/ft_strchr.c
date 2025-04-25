/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:40 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:04:12 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	to_search;

	to_search = (unsigned char)c;
	while (*s)
	{
		if (*s == to_search)
			return ((char *)s);
		s++;
	}
	if (*s == to_search)
		return ((char *)s);
	else
		return (NULL);
}
