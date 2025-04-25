/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:01:08 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:56:12 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_is_str_whitespace(char *str)
{
	while (*str)
	{
		if (!(*str == 32 || (*str >= 9 && *str <= 13)))
			return (0);
		str++;
	}
	return (1);
}

void	ft_puterror(char *cmd, char *cmd2, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (cmd2)
	{
		ft_putstr_fd(cmd2, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
	}
}
