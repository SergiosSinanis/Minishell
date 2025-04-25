/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:22:17 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:50:16 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_extract_key_value(char *token, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(token, '=');
	if (!equal_sign)
		return (0);
	*key = ft_strdup2(token, equal_sign - token);
	*value = ft_strdup(equal_sign + 1);
	if (!(*key) || !(*value))
	{
		free (*key);
		free (*value);
		return (0);
	}
	return (1);
}

int	ft_replace_env_var(char **envp, char *key, char *value)
{
	size_t	b;

	b = 0;
	while (envp[b])
	{
		if (ft_strncmp(envp[b], key, ft_strlen(key)) == 0
			&& envp[b][ft_strlen(key)] == '=')
		{
			free(envp[b]);
			envp[b] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
			if (!envp[b])
				return (0);
			ft_strlcpy(envp[b], key, ft_strlen(key) + 1);
			ft_strlcat(envp[b], "=", ft_strlen(key) + 2);
			ft_strlcat(envp[b], value, ft_strlen(key) + ft_strlen(value) + 2);
			free (key);
			free (value);
			return (1);
		}
		b++;
	}
	return (0);
}

int	ft_add_new_env_var(char ***envp, char *key, char *value)
{
	size_t	size;
	char	**new_env;

	size = 0;
	while ((*envp)[size])
		size++;
	new_env = ft_realloc(*envp, sizeof(char *) * (size),
			sizeof(char *) * (size + 2), 0);
	if (!new_env)
		return (0);
	free(*envp);
	*envp = new_env;
	(*envp)[size] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!(*envp)[size])
	{
		(*envp)[size] = NULL;
		return (0);
	}
	ft_strlcpy((*envp)[size], key, ft_strlen(key) + 1);
	ft_strlcat((*envp)[size], "=", ft_strlen(key) + 2);
	ft_strlcat((*envp)[size], value, ft_strlen(key) + ft_strlen(value) + 2);
	(*envp)[size + 1] = NULL;
	free (key);
	free (value);
	return (1);
}

int	ft_check_identifier(char **tokens, int *exit_status)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(tokens[1][0]) || tokens[1][0] == '_'))
	{
		ft_puterror("export", tokens[1], "not a valid identifier");
		*exit_status = 1;
		return (0);
	}
	while (tokens[1][i] && tokens[1][i] != '=')
	{
		if (!(ft_isalnum(tokens[1][i]) || tokens[1][i] == '_'))
		{
			ft_puterror("export", tokens[1], "not a valid identifier");
			*exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_export(char **envp, char **tokens, int *exit_status, int fd)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 1;
	if (!tokens[1])
		return (ft_sort_env(envp, fd));
	if (!ft_check_identifier(tokens, exit_status))
		return (envp);
	while (tokens[i])
	{
		if (ft_extract_key_value(tokens[i++], &key, &value))
		{
			if (!ft_replace_env_var(envp, key, value))
			{
				if (!ft_add_new_env_var(&envp, key, value))
				{
					ft_puterror("export", NULL, "memory allocation error");
					*exit_status = 1;
					return (envp);
				}
			}
		}
	}
	return (envp);
}
