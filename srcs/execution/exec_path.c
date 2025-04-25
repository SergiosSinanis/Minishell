/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:26:27 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:00 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_check_path(char *path, t_command *command)
{
	struct stat file_stat;

	if (!ft_strchr(path, '/'))
	{
		if (access(path, F_OK) != 0)
			ft_exit_error(path, strerror(errno), 1, command);
	}
	else
	{
		if (access(path, F_OK) != 0)
			ft_exit_error(path, strerror(errno), 127, command);
	}
	if (stat(path, &file_stat) != -1)
	{
		if (S_ISDIR(file_stat.st_mode))
			ft_exit_error(path, "Is a directory", 126, command);
	}
	if (access(path, X_OK) != 0)
		ft_exit_error(path, "Permission denied", 126, command);
}

char **ft_get_path_tab(char **env)
{
	char **paths;
	int i;

	i = 0;
	paths = NULL;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (env[i])
	{
		paths = ft_split(env[i] + 5, ':');
		return (paths);
	}
	return (NULL);
}

char *ft_join_path(char *cmd, char *path)
{
	char *path_tmp;
	char *joined_path;

	path_tmp = ft_strjoin(path, "/");
	joined_path = ft_strjoin(path_tmp, cmd);
	free(path_tmp);
	return (joined_path);
}

char *ft_get_path(char *cmd, char **env)
{
	char **paths;
	char *path;
	int i;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	else
	{
		paths = ft_get_path_tab(env);
		if (!paths)
			return (NULL);
		i = 0;
		while (paths[i])
		{
			path = ft_join_path(cmd, paths[i++]);
			if (access(path, F_OK) == 0)
			{
				ft_free_tab(paths);
				return (path);
			}
			free(path);
		}
		ft_free_tab(paths);
	}
	return (NULL);
}
