/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:54:53 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:48:57 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_tab_check_home(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int ft_tab_size(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void ft_cd(char **tokens, int *exit_status, char **env)
{
	char *path_to_go;
	char cwd[PATH_MAX];

	path_to_go = tokens[1];
	if (!path_to_go)
	{
		if (ft_tab_check_home(env))
			path_to_go = getenv("HOME");
		if (!path_to_go)
		{
			ft_error_builtin("cd", "HOME not set", 127, exit_status);
			return;
		}
	}
	if (ft_tab_size(tokens) > 2)
	{
		ft_error_builtin("cd", "too many arguments", 1, exit_status);
		return;
	}
	if (chdir(path_to_go) < 0 || !getcwd(cwd, sizeof(cwd)))
	{
		ft_puterror("cd", path_to_go, strerror(errno));
		*exit_status = 1;
	}
}

void ft_cd_invalid_opt(char **tokens, int *exit_code, char **env)
{
	if (tokens[1] && tokens[1][0] == '-')
	{
		ft_puterror("cd", tokens[1], "invalid option");
		*exit_code = 2;
		return;
	}
	ft_cd(tokens, exit_code, env);
}
