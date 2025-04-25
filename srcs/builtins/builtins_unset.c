/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:12:50 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:50:46 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_unset(char **envp, char **tokens, int *exit_status)
{
	size_t	i;
	size_t	b;

	i = 1;
	if (!ft_check_option(exit_status, tokens))
		return (envp);
	while (tokens[i])
	{
		b = 0;
		while (envp[b])
		{
			if (ft_strncmp(envp[b], tokens[i], ft_strlen(tokens[i])) == 0
				&& envp[b][ft_strlen(tokens[i])] == '=')
			{
				free(envp[b]);
				while (envp[++b])
					envp[b - 1] = envp[b];
				envp[b - 1] = NULL;
				break ;
			}
			b++;
		}
		i++;
	}
	return (envp);
}

int	ft_check_option(int *exit_status, char **tokens)
{
	if (tokens[1])
	{
		if (tokens[1][0] == '-')
		{
			ft_puterror("unset", tokens[1], "invalid option");
			*exit_status = 2;
			return (0);
		}
	}
	return (1);
}

char	**ft_duplicate_env(char **envp)
{
	char	**new_env;
	size_t	size;
	size_t	i;

	size = 0;
	while (envp[size])
		size++;
	new_env = malloc((size + 1) * sizeof(char *));
	if (!new_env)
	{
		perror("minishell: malloc");
		exit(1);
	}
	i = -1;
	while (envp[++i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			perror("minishell: ft_strdup");
			exit(1);
		}
	}
	new_env[size] = NULL;
	return (new_env);
}
