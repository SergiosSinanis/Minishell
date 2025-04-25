/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:06:53 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:02:12 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			total_size;
	size_t			i;
	void			*ptr;

	total_size = count * size;
	if (count != 0 && (total_size / count) != size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	p = (unsigned char *)ptr;
	while (i < total_size)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}
