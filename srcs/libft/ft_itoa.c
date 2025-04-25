/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:11:36 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 12:02:33 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nb_size(int nb)
{
	unsigned int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		counter = counter + 1;
	while (nb != 0)
	{
		nb = nb / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	nb;
	char			*result;

	len = ft_nb_size(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	if (n == 0)
		result[0] = '0';
	result[len] = '\0';
	while (nb != 0)
	{
		result[len - 1] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (result);
}
