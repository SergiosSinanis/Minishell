/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:22 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:49:53 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_exit(char **tokens, int *exit_status)
{
	if (tokens[1])
	{
		if (ft_is_number(tokens[1]))
			*exit_status = ft_atoi(tokens[1]);
		else
		{
			ft_putstr_fd("exit\n", 1);
			ft_puterror("exit", NULL, "numeric argument required");
			*exit_status = 2;
			return;
		}
		if (ft_tab_size(tokens) > 2)
		{
			ft_putstr_fd("exit\n", 1);
			ft_puterror("exit", NULL, "too many arguments");
			*exit_status = 1;
			return;
		}
	}
	ft_putstr_fd("exit\n", 1);
	ft_close_inherited_fds();
	exit(*exit_status);
}
