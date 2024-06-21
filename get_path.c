/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:08 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/20 13:25:43 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*access_rights(char **cmd)
{
	if (access(cmd[0], F_OK) == -1)
		error_handler_func(cmd, 1, 127);
	if (access(cmd[0], X_OK) == -1)
		error_handler_func(cmd, 2, 126);
	return (cmd[0]);
}

char	*get_path(char **cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	if (ft_strchr(cmd[0], '/') == 1)
		access_rights(cmd);
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, *cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/*static char	*get_envp(char **envp, char **cmd)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (&envp[i][5]);
	}
	error_handler_func(cmd, 1, 127);
	return (0);
}

char	*get_path(char **cmd, char **envp)
{
	char	**all_paths;
	char	*path_part;
	char	*path_to_cmd;
	int		i;

	i = -1;
	if (ft_strchr(cmd[0], '/') == 1)
		access_rights(cmd);
	all_paths = ft_split(get_envp(envp, cmd), ':');
	while (all_paths[++i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		if (!path_part)
			malloc_failure(cmd, all_paths);
		path_to_cmd = ft_strjoin(path_part, cmd[0]);
		free(path_part);
		if (!path_to_cmd)
			malloc_failure(cmd, all_paths);
		if (access(path_to_cmd, F_OK | X_OK) == 0)
		{
			free_func(all_paths);
			return (path_to_cmd);
		}
		free(path_to_cmd);
	}
	free_func(all_paths);
	error_handler_func(cmd, 3, 127);
	return (0);
}*/
