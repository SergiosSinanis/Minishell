/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:34:54 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:53:43 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	int exit_status;
	char **env;

	(void)argv;
	if (argc < 2)
	{
		env = ft_setup_environment(envp);
		ft_setup_signals();
		exit_status = ft_shell_loop(&env);
		ft_close_inherited_fds();
		ft_free_tab(env);
		return (exit_status);
	}
	else
		return (1);
}
