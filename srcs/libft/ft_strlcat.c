/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:29:37 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:04:32 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;

	if ((!src || !dst) && size == 0)
		return (0);
	i = 0;
	dest_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dest_size >= size)
		return (src_size + size);
	while (src[i] != '\0' && i < (size - dest_size - 1))
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	return (src_size + dest_size);
}
