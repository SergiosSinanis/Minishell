/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:58:36 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:54 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_digits(int nb)
{
	int	counter;

	counter = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		counter++;
	while (nb != 0)
	{
		nb = nb / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int nbr)
{
	long	nb;
	int		length;
	char	*result;

	nb = nbr;
	length = ft_count_digits(nbr);
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	result[length] = '\0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		result[0] = '0';
	while (nb > 0)
	{
		result[length - 1] = (nb % 10) + '0';
		nb = nb / 10;
		length--;
	}
	return (result);
}

int	ft_is_number(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '-' || argv[i] == '+')
		i++;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_question_mark(char *new_str, int exit_status)
{
	size_t	old_size;
	char	*exit_str;

	exit_str = ft_itoa(exit_status);
	if (exit_str)
	{
		old_size = ft_strlen(new_str);
		new_str = ft_realloc(new_str, old_size + 1,
				old_size + ft_strlen(exit_str) + 1, 1);
		ft_strlcat(new_str, exit_str, old_size + ft_strlen(exit_str) + 1);
		free(exit_str);
	}
	return (new_str);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size, int free_f)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	if (free_f == 1)
		free (ptr);
	return (new_ptr);
}
