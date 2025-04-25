/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:39:08 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:50:06 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_export(char **env, int output_fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (output_fd)
		{
			ft_putstr_fd("export ", output_fd);
			ft_putstr_fd(env[i], output_fd);
			ft_putstr_fd("\n", output_fd);
		}
		else
			printf("export %s\n", env[i]);
		i++;
	}
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**ft_sort_env(char **env, int output_fd)
{
	int		i;
	int		len;
	char	**envp;

	i = 0;
	len = 0;
	envp = ft_duplicate_env(env);
	while (envp[i] && envp[i + 1])
	{
		if (ft_strlen(envp[i]) > ft_strlen(envp[i + 1]))
			len = ft_strlen(envp[i]);
		else
			len = ft_strlen(envp[i + 1]);
		if (ft_strncmp(envp[i], envp[i + 1], len) > 0)
		{
			ft_swap(&envp[i], &envp[i + 1]);
			i = 0;
		}
		i++;
	}
	ft_print_export(envp, output_fd);
	ft_free_tab(envp);
	return (env);
}
