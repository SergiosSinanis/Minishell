/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssinanis <ssinanis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:41:06 by ssinanis          #+#    #+#             */
/*   Updated: 2025/04/09 11:51:15 by ssinanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_isbuiltin(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0 && ft_strlen(str) == 4)
		return (1);
	else if (ft_strncmp(str, "cd", 2) == 0 && ft_strlen(str) == 2)
		return (1);
	else if (ft_strncmp(str, "pwd", 3) == 0 && ft_strlen(str) == 3)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0 && ft_strlen(str) == 6)
		return (1);
	else if (ft_strncmp(str, "unset", 5) == 0 && ft_strlen(str) == 5)
		return (1);
	else if (ft_strncmp(str, "env", 3) == 0 && ft_strlen(str) == 3)
		return (1);
	else if (ft_strncmp(str, "exit", 4) == 0 && ft_strlen(str) == 4)
		return (1);
	return (0);
}

void ft_exec_builtin(char **tokens, char ***envp, int *exit_status, int fd)
{
	*exit_status = 0;
	if (ft_strncmp(tokens[0], "echo", ft_strlen("echo")) == 0)
		ft_echo(tokens, fd);
	else if (ft_strncmp(tokens[0], "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(fd, tokens, exit_status);
	else if (ft_strncmp(tokens[0], "env", ft_strlen("env")) == 0)
		ft_env(*envp, fd);
	else if (ft_strncmp(tokens[0], "cd", ft_strlen("cd")) == 0)
		ft_cd_invalid_opt(tokens, exit_status, *envp);
	else if (ft_strncmp(tokens[0], "export", ft_strlen("export")) == 0)
		*envp = ft_export(*envp, tokens, exit_status, fd);
	else if (ft_strncmp(tokens[0], "unset", ft_strlen("unset")) == 0)
		*envp = ft_unset(*envp, tokens, exit_status);
	else if (ft_strncmp(tokens[0], "exit", ft_strlen("exit")) == 0)
		ft_exit(tokens, exit_status);
}

int ft_error_builtin(char *path, char *error, int error_code, int *exit_code)
{
	ft_puterror(path, NULL, error);
	*exit_code = error_code;
	return (0);
}

int ft_check_path_builtin(char *path, int *exit_code)
{
	struct stat file_stat;

	if (!ft_strchr(path, '/'))
	{
		if (access(path, F_OK) != 0)
			return (ft_error_builtin(path, strerror(errno), 1, exit_code));
	}
	else
	{
		if (access(path, F_OK) != 0)
			return (ft_error_builtin(path, strerror(errno), 127, exit_code));
	}
	if (stat(path, &file_stat) != -1)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (ft_error_builtin(path, "Is a directory", 126, exit_code));
	}
	if (access(path, X_OK) != 0)
		return (ft_error_builtin(path, "Permission denied", 126, exit_code));
	return (1);
}

int ft_check_redirection(t_command *command, int *exit_code)
{
	int flag;

	flag = 1;
	if (command->input_fd == -1)
		flag = ft_check_path_builtin(command->input_file, exit_code);
	if (command->output_fd == -1)
		flag = ft_check_path_builtin(command->output_file, exit_code);
	return (flag);
}
