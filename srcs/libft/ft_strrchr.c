/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:35:06 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:05:04 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	to_search;

	i = ft_strlen(s);
	to_search = (unsigned char)c;
	while (i >= 0)
	{
		if (s[i] == to_search)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
