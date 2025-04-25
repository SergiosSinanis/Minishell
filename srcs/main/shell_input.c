/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:32:22 by ssinanis          #+#    #+#             */
/*   Updated: 2025/02/24 18:32:25 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_setup_environment(char **envp)
{
	char	**env;

	if ((envp[0]))
		env = ft_duplicate_env(envp);
	else
		env = ft_minimal_env(envp);
	return (env);
}

int	ft_shell_input(char **input)
{
	*input = readline("minishell> ");
	if (!*input)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	return (0);
}

int	ft_shell_special_input(char *input)
{
	if (input[0] == '\0' || ft_is_str_whitespace(input)
		|| input[0] == ':' || input[0] == '!')
	{
		free(input);
		return (1);
	}
	if (ft_strlen(input) == 1 && input[0] == '$')
	{
		ft_puterror("$", NULL, "command not found");
		free (input);
		return (127);
	}
	return (-1);
}

char	*ft_shell_expansion(char *input, char **env, int exit_status)
{
	char	*input_expand;

	if (input[0] == '$' && !ft_strchr(input, ' '))
	{
		input_expand = ft_expand(input, env, exit_status);
		if (ft_strlen(input_expand) == 0
			|| ft_strncmp(input_expand, input, ft_strlen(input)) == 0)
		{
			free(input);
			free(input_expand);
			return (NULL);
		}
	}
	else
		input_expand = ft_expand(input, env, exit_status);
	free(input);
	return (input_expand);
}
